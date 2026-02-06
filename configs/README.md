# CPL Configuration Presets

This directory contains preset configurations for the CPL build system. These configuration files can be used to quickly set up the build environment for different use cases.

## Available Configurations

### `defconfig`
**Default configuration** - Balanced configuration with most features enabled.
- Performance optimizations enabled
- Debug information included
- All library modules enabled
- All tests enabled
- All benchmarks enabled
- All tools enabled

**Usage:**
```bash
make defconfig
```

### `allnoconfig`
**Minimal configuration** - All features disabled.
- Useful for testing minimal builds
- Good starting point for custom configurations

**Usage:**
```bash
make allnoconfig
```

### `allyesconfig`
**Full configuration** - All features enabled.
- All compiler options enabled (including sanitizers)
- All library modules enabled
- All tests enabled
- All benchmarks enabled
- All tools enabled

**Usage:**
```bash
make allyesconfig
```

### `debug_defconfig`
**Debug configuration** - Optimized for debugging.
- Debug information enabled
- AddressSanitizer enabled
- UndefinedBehaviorSanitizer enabled
- No optimization flags
- All tests enabled
- Benchmarks disabled (sanitizers affect performance)

**Usage:**
```bash
make debug_defconfig
```

### `release_defconfig`
**Release configuration** - Optimized for production.
- Maximum performance optimizations
- No debug information
- No sanitizers
- RELEASE build flag enabled
- Tests disabled
- Benchmarks enabled for performance validation

**Usage:**
```bash
make release_defconfig
```

### `minimal_defconfig`
**Minimal library configuration** - Core library only.
- Core utilities only (xcore, xutility)
- Basic optimizations
- Single test for core functionality
- No additional modules

**Usage:**
```bash
make minimal_defconfig
```

## Usage

To use a preset configuration:

1. Load the configuration:
   ```bash
   make <config_name>
   # Example: make debug_defconfig
   ```

2. Optionally customize with menuconfig:
   ```bash
   make menuconfig
   ```

3. Build:
   ```bash
   make
   ```

## Creating Custom Configurations

To create your own configuration preset:

1. Start with an existing configuration or use menuconfig:
   ```bash
   make menuconfig
   ```

2. Save your configuration to a new file:
   ```bash
   cp .config configs/my_custom_defconfig
   ```

3. Use your custom configuration:
   ```bash
   cp configs/my_custom_defconfig .config
   make oldconfig
   ```

## Configuration File Format

Configuration files use the Kconfig format:
- `CONFIG_OPTION=y` - Option enabled
- `# CONFIG_OPTION is not set` - Option explicitly disabled
- Comments start with `#`
