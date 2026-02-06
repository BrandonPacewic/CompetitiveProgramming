#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# Copyright (c) Brandon Pacewic
"""
Configuration file generator for Kbuild system.
Generates auto.conf (Makefile format) and autoconf.h (C header format) from .config.
"""

import os
import sys
import subprocess
import shutil
from pathlib import Path

def find_kconfiglib():
    """Check if kconfiglib is available."""
    try:
        import kconfiglib
        return kconfiglib
    except ImportError:
        return None

def generate_with_kconfiglib(kconfig_file, config_file):
    """Generate auto.conf and autoconf.h using kconfiglib."""
    import kconfiglib

    # Load Kconfig
    kconf = kconfiglib.Kconfig(kconfig_file)

    # Load .config if it exists
    if os.path.exists(config_file):
        kconf.load_config(config_file)
    else:
        print(f"WARNING: {config_file} not found, using defaults", file=sys.stderr)

    # Get output paths from environment or defaults
    autoconf_path = os.environ.get('KCONFIG_AUTOCONFIG', 'include/config/auto.conf')
    autoheader_path = os.environ.get('KCONFIG_AUTOHEADER', 'include/generated/autoconf.h')

    # Create output directories
    os.makedirs(os.path.dirname(autoconf_path), exist_ok=True)
    os.makedirs(os.path.dirname(autoheader_path), exist_ok=True)

    # Generate auto.conf (Makefile format)
    generate_autoconf(kconf, autoconf_path)

    # Generate autoconf.h (C header format)
    generate_autoheader(kconf, autoheader_path)

    # Generate dependency file
    generate_autodep(kconf, autoconf_path)

    return 0

def generate_autoconf(kconf, output_path):
    """Generate auto.conf in Makefile format."""
    import kconfiglib

    # Write to temporary file first (atomic operation)
    tmp_path = output_path + '.tmp'

    with open(tmp_path, 'w') as f:
        f.write('#\n')
        f.write('# Automatically generated file; DO NOT EDIT.\n')
        f.write(f'# {kconf.mainmenu_text}\n')
        f.write('#\n')

        for sym in kconf.unique_defined_syms:
            # Skip if symbol has no value or shouldn't be written
            if sym.type == kconfiglib.UNKNOWN:
                continue

            # Get symbol value
            val = sym.str_value

            if sym.type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                if val == 'y':
                    f.write(f'CONFIG_{sym.name}=y\n')
                elif val == 'm':
                    f.write(f'CONFIG_{sym.name}=m\n')
                else:
                    f.write(f'# CONFIG_{sym.name} is not set\n')
            elif sym.type == kconfiglib.STRING:
                if val:
                    f.write(f'CONFIG_{sym.name}="{val}"\n')
            elif sym.type in (kconfiglib.INT, kconfiglib.HEX):
                if val:
                    f.write(f'CONFIG_{sym.name}={val}\n')

    # Atomic rename
    os.rename(tmp_path, output_path)

def generate_autoheader(kconf, output_path):
    """Generate autoconf.h in C header format."""
    import kconfiglib

    # Write to temporary file first (atomic operation)
    tmp_path = output_path + '.tmp'

    with open(tmp_path, 'w') as f:
        f.write('/*\n')
        f.write(' * Automatically generated file; DO NOT EDIT.\n')
        f.write(f' * {kconf.mainmenu_text}\n')
        f.write(' */\n')
        f.write('#ifndef __AUTOCONF_H\n')
        f.write('#define __AUTOCONF_H\n')
        f.write('\n')

        for sym in kconf.unique_defined_syms:
            # Skip if symbol has no value or shouldn't be written
            if sym.type == kconfiglib.UNKNOWN:
                continue

            # Get symbol value
            val = sym.str_value

            if sym.type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                if val == 'y':
                    f.write(f'#define CONFIG_{sym.name} 1\n')
                elif val == 'm':
                    f.write(f'#define CONFIG_{sym.name}_MODULE 1\n')
                else:
                    f.write(f'/* #undef CONFIG_{sym.name} */\n')
            elif sym.type == kconfiglib.STRING:
                if val:
                    f.write(f'#define CONFIG_{sym.name} "{val}"\n')
            elif sym.type == kconfiglib.INT:
                if val:
                    f.write(f'#define CONFIG_{sym.name} {val}\n')
            elif sym.type == kconfiglib.HEX:
                if val:
                    f.write(f'#define CONFIG_{sym.name} 0x{val}\n')

        f.write('\n')
        f.write('#endif /* __AUTOCONF_H */\n')

    # Atomic rename
    os.rename(tmp_path, output_path)

def generate_autodep(kconf, autoconf_path):
    """Generate auto.conf.cmd dependency file."""
    import kconfiglib

    dep_path = autoconf_path + '.cmd'

    with open(dep_path, 'w') as f:
        f.write(f'deps_config := \\\n')

        # Include all Kconfig files that were loaded
        kconfig_files = set()

        # Add main Kconfig
        kconfig_files.add('Kconfig')

        # Walk through all symbols and get their Kconfig files
        for node in kconf.node_iter():
            if node.filename:
                kconfig_files.add(node.filename)

        # Write dependencies
        for kfile in sorted(kconfig_files):
            f.write(f'\t{kfile} \\\n')

        f.write('\n')
        f.write(f'include/config/auto.conf: \\\n')
        f.write(f'\t$(deps_config)\n')
        f.write('\n')

        # List all files
        for kfile in sorted(kconfig_files):
            f.write(f'{kfile}:\n')

def generate_with_conf_tool(kconfig_file, config_file):
    """Generate using conf tool from kconfig-frontends."""
    # Look for conf tool
    conf_paths = [
        'scripts/kconfig/conf',
        'scripts/kconfig-frontends/frontends/conf/conf',
        shutil.which('conf'),
    ]

    conf_tool = None
    for path in conf_paths:
        if path and os.path.exists(path):
            conf_tool = path
            break

    if not conf_tool:
        return None

    # Set up environment
    env = os.environ.copy()
    config_file = env.get('KCONFIG_CONFIG', config_file)
    autoconf_path = env.get('KCONFIG_AUTOCONFIG', 'include/config/auto.conf')
    autoheader_path = env.get('KCONFIG_AUTOHEADER', 'include/generated/autoconf.h')

    env['KCONFIG_CONFIG'] = config_file
    env['KCONFIG_AUTOCONFIG'] = autoconf_path
    env['KCONFIG_AUTOHEADER'] = autoheader_path

    # Create output directories
    os.makedirs(os.path.dirname(autoconf_path), exist_ok=True)
    os.makedirs(os.path.dirname(autoheader_path), exist_ok=True)

    # Run conf tool with --syncconfig (or --silentoldconfig for older versions)
    try:
        result = subprocess.run(
            [conf_tool, '--syncconfig', kconfig_file],
            env=env,
            capture_output=True
        )
        if result.returncode == 0:
            return 0

        # Try older option name
        result = subprocess.run(
            [conf_tool, '--silentoldconfig', kconfig_file],
            env=env,
            capture_output=True
        )
        return result.returncode
    except Exception:
        return None

def generate_with_simple_parser(config_file):
    """Generate auto.conf and autoconf.h using simple .config parser.

    This is a fallback when kconfiglib is not available. It directly
    parses the .config file without Kconfig validation.
    """
    if not os.path.exists(config_file):
        print(f"ERROR: {config_file} not found", file=sys.stderr)
        return 1

    # Get output paths from environment or defaults
    autoconf_path = os.environ.get('KCONFIG_AUTOCONFIG', 'include/config/auto.conf')
    autoheader_path = os.environ.get('KCONFIG_AUTOHEADER', 'include/generated/autoconf.h')

    # Create output directories
    os.makedirs(os.path.dirname(autoconf_path), exist_ok=True)
    os.makedirs(os.path.dirname(autoheader_path), exist_ok=True)

    # Parse .config file
    configs = {}
    with open(config_file, 'r') as f:
        for line in f:
            line = line.strip()

            # Skip empty lines and comments
            if not line or line.startswith('#'):
                # Check for "# CONFIG_XXX is not set" pattern
                if line.startswith('# CONFIG_') and ' is not set' in line:
                    # Extract the config name
                    parts = line.split()
                    if len(parts) >= 2:
                        config_name = parts[1]
                        configs[config_name] = 'n'
                continue

            # Parse CONFIG_XXX=y/m/n or CONFIG_XXX="value"
            if line.startswith('CONFIG_'):
                if '=' in line:
                    key, value = line.split('=', 1)
                    configs[key] = value

    # Generate auto.conf
    generate_autoconf_simple(configs, autoconf_path, config_file)

    # Generate autoconf.h
    generate_autoheader_simple(configs, autoheader_path, config_file)

    return 0

def generate_autoconf_simple(configs, output_path, config_file):
    """Generate auto.conf from parsed config dictionary."""
    tmp_path = output_path + '.tmp'

    with open(tmp_path, 'w') as f:
        f.write('#\n')
        f.write('# Automatically generated file; DO NOT EDIT.\n')
        f.write('# CPL Configuration\n')
        f.write('#\n')

        for key in sorted(configs.keys()):
            value = configs[key]
            if value == 'n':
                f.write(f'# {key} is not set\n')
            elif value == 'y':
                f.write(f'{key}=y\n')
            elif value == 'm':
                f.write(f'{key}=m\n')
            elif value.startswith('"') and value.endswith('"'):
                # String value
                f.write(f'{key}={value}\n')
            else:
                # Numeric value
                f.write(f'{key}={value}\n')

    # Atomic rename
    os.rename(tmp_path, output_path)

def generate_autoheader_simple(configs, output_path, config_file):
    """Generate autoconf.h from parsed config dictionary."""
    tmp_path = output_path + '.tmp'

    with open(tmp_path, 'w') as f:
        f.write('/*\n')
        f.write(' * Automatically generated file; DO NOT EDIT.\n')
        f.write(' * CPL Configuration\n')
        f.write(' */\n')
        f.write('#ifndef __AUTOCONF_H\n')
        f.write('#define __AUTOCONF_H\n')
        f.write('\n')

        for key in sorted(configs.keys()):
            value = configs[key]
            if value == 'n':
                f.write(f'/* #undef {key} */\n')
            elif value == 'y':
                f.write(f'#define {key} 1\n')
            elif value == 'm':
                f.write(f'#define {key}_MODULE 1\n')
            elif value.startswith('"') and value.endswith('"'):
                # String value
                f.write(f'#define {key} {value}\n')
            else:
                # Try to detect hex values
                if value.startswith('0x') or value.startswith('0X'):
                    f.write(f'#define {key} {value}\n')
                else:
                    # Numeric value
                    try:
                        int(value)
                        f.write(f'#define {key} {value}\n')
                    except ValueError:
                        # Treat as string if not a number
                        f.write(f'#define {key} "{value}"\n')

        f.write('\n')
        f.write('#endif /* __AUTOCONF_H */\n')

    # Atomic rename
    os.rename(tmp_path, output_path)

def print_help():
    """Print installation help."""
    print("""
WARNING: Using fallback .config parser without Kconfig validation.

For better integration, install one of the following:

Option 1: Install kconfiglib (Python, recommended)
    pip install --user kconfiglib
    OR
    sudo apt install python3-kconfiglib    # On Debian/Ubuntu

Option 2: Build kconfig-frontends from source
    cd scripts/kconfig-frontends
    ./bootstrap
    ./configure
    make

Option 3: Install system kconfig tools
    sudo apt install kconfig-frontends      # On Debian/Ubuntu
    sudo dnf install kconfig-frontends      # On Fedora
    sudo pacman -S kconfig-frontends        # On Arch
""", file=sys.stderr)

def main():
    # Get paths from arguments or defaults
    kconfig_file = sys.argv[1] if len(sys.argv) > 1 else 'Kconfig'
    config_file = sys.argv[2] if len(sys.argv) > 2 else '.config'

    # Override from environment
    config_file = os.environ.get('KCONFIG_CONFIG', config_file)

    # Try kconfiglib first (preferred method)
    kconfiglib = find_kconfiglib()
    if kconfiglib:
        try:
            return generate_with_kconfiglib(kconfig_file, config_file)
        except Exception as e:
            print(f"ERROR: Failed with kconfiglib: {e}", file=sys.stderr)

    # Try conf tool as fallback
    result = generate_with_conf_tool(kconfig_file, config_file)
    if result is not None:
        return result

    # Use simple parser as final fallback
    print_help()
    try:
        return generate_with_simple_parser(config_file)
    except Exception as e:
        print(f"ERROR: Failed to generate config files: {e}", file=sys.stderr)
        return 1

if __name__ == '__main__':
    sys.exit(main())
