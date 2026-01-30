# SPDX-License-Identifier: MIT
# Copyright (c) Brandon Pacewic

# CPL (Competitive Programming Library) - Kbuild-based build system
# This is the top-level Makefile for the project.

VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
NAME = CPL

# *DOCUMENTATION*
# To see a list of typical targets execute "make help"
# More info can be found in BUILD.md

# That's our default target when none is given on the command line
PHONY := _all
_all:

# We are using a recursive build, so we need to do a little thinking
# to get the ordering right.
#
# Most importantly: sub-Makefiles should only ever modify files in
# their own directory. If in some directory we have a dependency on
# a file in another dir (which doesn't happen often, but it's often
# unavoidable when linking the built-in.a targets which finally
# turn into the libraries), we will call a sub make in that other
# dir, and after that we are sure that everything which is in that
# other dir is now up to date.

# Cancel implicit rules on top Makefile
$(CURDIR)/Makefile Makefile: ;

ifneq ($(sub_make_done),1)

# Do not use make's built-in rules and variables
# (this increases performance and avoids hard-to-debug behaviour)
MAKEFLAGS += -rR

# Avoid funny character set dependencies
unexport LC_ALL
LC_COLLATE=C
LC_NUMERIC=C
export LC_COLLATE LC_NUMERIC

# Avoid interference with shell env settings
unexport GREP_OPTIONS

# We need bash for various scripts
SHELL := bash

# Make variables (CC, etc...)
CXX	  := $(if $(CXX),$(CXX),g++)
AR	  := $(if $(AR),$(AR),ar)
LD	  := $(CXX)
CPP	  := $(CXX) -E
STRIP := $(if $(STRIP),$(STRIP),strip)

export CXX AR LD CPP STRIP

# Use USERINCLUDE when you must reference the UAPI directories only.
USERINCLUDE = \
		-I$(srctree)/cpl/inc

# Use CPLINCLUDES when you must reference library headers
CPLINCLUDES = \
		-I$(srctree)/cpl/inc

CPPFLAGS := -D__CPL__ $(CPLINCLUDES)

KBUILD_CXXFLAGS := -std=c++20 -Wall -Wextra

export CPPFLAGS KBUILD_CXXFLAGS CPLINCLUDES

# Read KERNELRELEASE from include/config/kernel.release (if it exists)
KERNELRELEASE = $(shell cat include/config/kernel.release 2> /dev/null)
CPLRELEASE = $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)

# SUBARCH tells the usermode build what the underlying arch is.  That is set
# first, and if a usermode build is happening, the "ARCH=um" on the command
# line overrides the setting of ARCH below.  If a native build is happening,
# then ARCH is assigned, getting whatever value it gets normally, and
# SUBARCH is subsequently ignored.

SUBARCH := $(shell uname -m | sed -e s/i.86/x86/ -e s/x86_64/x86/ \
				  -e s/sun4u/sparc64/ \
				  -e s/arm.*/arm/ -e s/sa110/arm/ \
				  -e s/s390x/s390/ -e s/parisc64/parisc/ \
				  -e s/ppc.*/powerpc/ -e s/mips.*/mips/ \
				  -e s/sh[234].*/sh/ -e s/aarch64.*/arm64/ \
				  -e s/riscv.*/riscv/)

# Cross compiling and selecting different set of gcc/bin-utils
# ---------------------------------------------------------------------------
#
# When performing cross compilation for other architectures ARCH shall be set
# to the target architecture. (See arch/* for the possibilities).
# ARCH can be set during invocation of make:
# make ARCH=ia64
# Another way is to have ARCH set in the environment.
# The default ARCH is the host where make is executed.

# CROSS_COMPILE can be set on the command line
# make CROSS_COMPILE=ia64-linux-
# Alternatively CROSS_COMPILE can be set in the environment.
# Default value for CROSS_COMPILE is not to prefix executables
# Note: Some architectures assign CROSS_COMPILE in their arch/*/Makefile
ARCH		  ?= $(SUBARCH)
CROSS_COMPILE ?= $(CONFIG_CROSS_COMPILE:"%"=%)

# Architecture as present in compile.h
UTS_MACHINE := $(ARCH)

KCONFIG_CONFIG ?= .config
export KCONFIG_CONFIG

# KBUILD_VERBOSE is set to V= on the command line
#   V=0 means quiet output (default)
#   V=1 means verbose output
#   V=2 means give reason for rebuild of target

ifdef V
	ifeq ("$(origin V)", "command line")
		KBUILD_VERBOSE = $(V)
	endif
endif
ifndef KBUILD_VERBOSE
	KBUILD_VERBOSE = 0
endif

ifeq ($(KBUILD_VERBOSE),1)
	quiet =
	Q =
else
	quiet=quiet_
	Q = @
endif

# If the user is running make -s (silent mode), suppress echoing of
# commands

ifneq ($(findstring s,$(filter-out --%,$(MAKEFLAGS))),)
	quiet=silent_
endif

export quiet Q KBUILD_VERBOSE

# Call a source code checker (by default, "sparse") as part of the
# C compilation.
#
# Use 'make C=1' to enable checking of only re-compiled files.
# Use 'make C=2' to enable checking of *all* source files, regardless
# of whether they are re-compiled or not.
#
# See the file "Documentation/dev-tools/sparse.rst" for more details,
# including where to get the "sparse" utility.

ifeq ("$(origin C)", "command line")
	KBUILD_CHECKSRC = $(C)
endif
ifndef KBUILD_CHECKSRC
	KBUILD_CHECKSRC = 0
endif

export KBUILD_CHECKSRC

# Use make M=dir to specify directory of external module to build
# Old syntax make ... SUBDIRS=$PWD is still supported
# Setting the environment variable KBUILD_EXTMOD take precedence
ifdef SUBDIRS
	KBUILD_EXTMOD ?= $(SUBDIRS)
endif

ifeq ("$(origin M)", "command line")
	KBUILD_EXTMOD := $(M)
endif

ifeq ($(KBUILD_SRC),)
	# building in the source tree
	srctree := .
else
	ifeq ($(KBUILD_SRC)/,$(dir $(CURDIR)))
	    # building in a subdirectory of the source tree
	    srctree := ..
	else
		srctree := $(KBUILD_SRC)
	endif
endif

export srctree

objtree := .
src		:= $(srctree)
obj		:= $(objtree)
VPATH   := $(srctree)

export srctree objtree VPATH

# To put more focus on warnings, be less verbose as default
# Use 'make V=1' to see the full commands

# Handle O= option to locate all output files in a separate directory
ifeq ("$(origin O)", "command line")
	KBUILD_OUTPUT := $(O)
endif

# That's our default target when none is given on the command line
PHONY += all
ifeq ($(KBUILD_EXTMOD),)
_all: all
else
_all: modules
endif

ifneq ($(KBUILD_OUTPUT),)
# Invoke a second make in the output directory, passing relevant variables
# check that the output directory actually exists
saved-output := $(KBUILD_OUTPUT)
KBUILD_OUTPUT := $(shell mkdir -p $(KBUILD_OUTPUT) && cd $(KBUILD_OUTPUT) \
								&& /bin/pwd)
$(if $(KBUILD_OUTPUT),, \
     $(error failed to create output directory "$(saved-output)"))

PHONY += $(MAKECMDGOALS) sub-make

$(filter-out _all sub-make $(CURDIR)/Makefile, $(MAKECMDGOALS)) _all: sub-make
	@:

sub-make:
	$(Q)ln -fsn $(CURDIR) $(KBUILD_OUTPUT)/source
	$(Q)$(MAKE) -C $(KBUILD_OUTPUT) KBUILD_SRC=$(CURDIR) \
	-f $(CURDIR)/Makefile $(filter-out _all sub-make,$(MAKECMDGOALS)) \
	sub_make_done=1

# Leave processing to above invocation of make
skip-makefile := 1
endif # ifneq ($(KBUILD_OUTPUT),)
endif # ifeq ($(sub_make_done),1)

# We process the rest of the Makefile if this is the final invocation of make
ifeq ($(skip-makefile),)

# Include the Kbuild include file for macros
include scripts/Kbuild.include

# If building an external module we do not care about the all: rule
# but instead _all depend on modules
PHONY += all
all: cpl tests tools

# Shorthand for building targets
PHONY += cpl tests benchmarks tools
cpl: build-cpl
tests: build-tests
benchmarks: build-benchmarks
tools: build-tools

# The actual objects are generated when descending,
# make sure no implicit rule kicks in
$(sort $(vmlinux-deps)): $(vmlinux-dirs) ;

# Handle descending into subdirectories listed in $(vmlinux-dirs)
# Preset locale variables to speed up the build process. Limit locale
# tweaks to this spot to avoid wrong language settings when running
# make menuconfig etc.
# Error messages still appears in the original language

PHONY += $(vmlinux-dirs)
$(vmlinux-dirs): prepare scripts
	$(Q)$(MAKE) $(build)=$@

# Build targets that will be handled by sub-makes
PHONY += build-cpl build-tests build-benchmarks build-tools
build-cpl:
	$(Q)$(MAKE) $(build)=cpl

build-tests: build-cpl
	$(Q)$(MAKE) $(build)=tests

build-benchmarks: build-cpl
	$(Q)$(MAKE) $(build)=benchmarks

build-tools:
	$(Q)$(MAKE) $(build)=tools

###
# Cleaning is done on three levels.
# make clean     Delete most generated files
#                Leave enough to build external modules
# make mrproper  Delete the current configuration, and all generated files
# make distclean Remove editor backup files, patch leftover files and the like

# Directories & files removed with 'make clean'
CLEAN_DIRS  := $(objtree)
CLEAN_FILES :=

# Directories & files removed with 'make mrproper'
MRPROPER_DIRS  := include/config include/generated \
		          .tmp_objdiff

MRPROPER_FILES := .config .config.old .version .old_version                 \
		          Module.symvers tags TAGS cscope* GPATH GTAGS GRTAGS GSYMS \
		          signing_key.pem signing_key.priv signing_key.x509	        \
		          x509.genkey extra_certificates signing_key.x509.keyid	    \
		          signing_key.x509.signer vmlinux-gdb.py

# clean - Delete most generated files but keep the config
#
PHONY += clean archclean vmlinuxclean
clean: archclean vmlinuxclean

# Recursively clean directories using Makefile.clean
PHONY += $(clean-dirs)
$(clean-dirs):
	$(Q)$(MAKE) $(clean)=$@

vmlinuxclean:
	$(Q)$(MAKE) $(clean)=cpl
	$(Q)$(MAKE) $(clean)=tests
	$(Q)$(MAKE) $(clean)=benchmarks
	$(Q)$(MAKE) $(clean)=tools

archclean:
	$(Q)$(if $(CLEAN_FILES), rm -f $(CLEAN_FILES))

# mrproper - Delete all generated files + config + various backup files
#
PHONY += mrproper
mrproper: clean
	$(Q)rm -rf $(MRPROPER_DIRS)
	$(Q)rm -f $(MRPROPER_FILES)

# distclean - Remove editor backup files, patch leftover files and the like
#
PHONY += distclean
distclean: mrproper
	$(Q)find $(srctree) \( -name '*.orig' -o -name '*.rej' -o -name '*~' \
		-o -name '*.bak' -o -name '#*#' -o -name '*%' \
		-o -name 'core' \) \
		-type f -print | xargs rm -f

# Prepare step - currently minimal
PHONY += prepare
prepare:
	@:

# Scripts target - for building host programs needed during build
PHONY += scripts
scripts:
	@:

# Help target
PHONY += help
help:
	@echo  'Cleaning targets:'
	@echo  '  clean           - Remove most generated files but keep the config'
	@echo  '  mrproper        - Remove all generated files + config + various backup files'
	@echo  '  distclean       - mrproper + remove editor backup files, patch leftover files and the like'
	@echo  ''
	@echo  'Build targets:'
	@echo  '  all             - Build cpl library, tests, and tools (default)'
	@echo  '  cpl             - Build the CPL library'
	@echo  '  tests           - Build all tests'
	@echo  '  benchmarks      - Build all benchmarks'
	@echo  '  tools           - Build all tools'
	@echo  ''
	@echo  'Other generic targets:'
	@echo  '  help            - This help message'
	@echo  ''
	@echo  'Execute "make" or "make all" to build all targets marked with *'
	@echo  ''
	@echo  'Make variables (set on command line):'
	@echo  '  V=0|1|2         - 0 => quiet build (default), 1 => verbose build, 2 => give reason for rebuild'
	@echo  '  O=dir           - Output directory for out-of-tree builds'
	@echo  '  C=1|2           - Run checker on re-compiled (1) or all (2) files'
	@echo  '  CROSS_COMPILE=prefix - Prefix for cross-compilation tools (e.g., aarch64-linux-gnu-)'
	@echo  ''
	@echo  'Example:'
	@echo  '  make V=1        - Build with verbose output'
	@echo  '  make O=build    - Build out-of-tree in ./build directory'
	@echo  '  make clean      - Clean generated files'

# Single targets
# ---------------------------------------------------------------------------
# Single targets are compatible with:
# - build with mixed source and output
# - build with separate output dir 'make O=...'
# - external modules
#
#  target-dir => where to store outputfile
#  build-dir  => directory in kernel source tree to use

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)

endif # skip-makefile

# Declare the contents of the .PHONY variable as phony
.PHONY: $(PHONY)
