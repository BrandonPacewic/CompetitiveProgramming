#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# Copyright (c) Brandon Pacewic
"""
Menuconfig wrapper that tries multiple backends for Kconfig configuration.
"""

import os
import sys
import subprocess
import shutil

def find_kconfiglib():
    """Try to import kconfiglib or find menuconfig tool."""
    try:
        import kconfiglib
        return 'kconfiglib', kconfiglib
    except ImportError:
        pass

    # Check for system menuconfig tools
    tools = ['menuconfig', 'kconfig-mconf', 'mconf']
    for tool in tools:
        if shutil.which(tool):
            return 'external', tool

    return None, None

def run_kconfiglib_menuconfig(config_file):
    """Run menuconfig using kconfiglib Python module."""
    import kconfiglib
    import menuconfig

    # Set Kconfig file from environment or default
    kconfig_file = os.environ.get('KCONFIG_CONFIG', config_file)

    # Run menuconfig
    os.environ['KCONFIG_CONFIG'] = kconfig_file
    menuconfig.menuconfig('Kconfig')

def run_external_menuconfig(tool, config_file):
    """Run external menuconfig tool."""
    env = os.environ.copy()
    env['KCONFIG_CONFIG'] = config_file
    return subprocess.run([tool, 'Kconfig'], env=env).returncode

def print_help():
    """Print installation help for menuconfig tools."""
    print("""
ERROR: No Kconfig menuconfig tool found!

To use menuconfig, you need one of the following:

Option 1: Install kconfiglib (Python, recommended)
    pip install --user kconfiglib
    OR
    sudo apt install python3-kconfiglib    # On Debian/Ubuntu

Option 2: Build kconfig-frontends from source
    cd scripts/kconfig-frontends
    ./bootstrap
    ./configure
    make
    sudo make install

Option 3: Install system kconfig tools
    sudo apt install kconfig-frontends      # On Debian/Ubuntu
    sudo dnf install kconfig-frontends      # On Fedora
    sudo pacman -S kconfig-frontends        # On Arch

For now, you can manually edit the .config file or use one of the preset configs:
    cp configs/default.config .config
    make oldconfig
""", file=sys.stderr)

def main():
    if len(sys.argv) < 2:
        config_file = '.config'
    else:
        config_file = sys.argv[1]

    # Find available backend
    backend_type, backend = find_kconfiglib()

    if backend_type is None:
        print_help()
        return 1

    # Run menuconfig with available backend
    try:
        if backend_type == 'kconfiglib':
            run_kconfiglib_menuconfig(config_file)
            return 0
        elif backend_type == 'external':
            return run_external_menuconfig(backend, config_file)
    except Exception as e:
        print(f"ERROR: Failed to run menuconfig: {e}", file=sys.stderr)
        print_help()
        return 1

if __name__ == '__main__':
    sys.exit(main())
