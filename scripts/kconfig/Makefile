# SPDX-License-Identifier: MIT
# Copyright (c) Brandon Pacewic
# Makefile for building kconfig tools

# Use kconfig-frontends sources
KCONFIG_SRC := $(srctree)/scripts/kconfig-frontends

# Parser sources from libs/parser
PARSER_SRC := $(KCONFIG_SRC)/libs/parser
PARSER_OBJS := confdata.o expr.o menu.o symbol.o util.o

# lxdialog sources from libs/lxdialog
LXDIALOG_SRC := $(KCONFIG_SRC)/libs/lxdialog
LXDIALOG_OBJS := checklist.o inputbox.o menubox.o textbox.o util.o yesno.o

# mconf sources from frontends/mconf
MCONF_SRC := $(KCONFIG_SRC)/frontends/mconf

# All object files needed for mconf
MCONF_OBJS := mconf.o $(PARSER_OBJS) $(LXDIALOG_OBJS)

# Generated files from parser (lexer and parser)
GEN_OBJS := lconf.lex.o yconf.tab.o

# Output binary
MCONF := mconf

# Compiler flags
HOSTCC := gcc
HOSTCXX := g++
CFLAGS := -Wall -Wextra -O2 -Wno-unused-parameter -Wno-sign-compare
CFLAGS += -I$(PARSER_SRC) -I$(KCONFIG_SRC)/libs -I$(MCONF_SRC)
CFLAGS += -DCURSES_LOC="<ncurses.h>"
CFLAGS += -DKBUILD_NO_NLS
CFLAGS += -D_GNU_SOURCE
CFLAGS += -DPATH_MAX=4096

# Linker flags
LDFLAGS := -lncurses

# Check for ncurses library
NCURSES_CHECK := $(shell echo "int main(){}" | $(HOSTCC) -x c - -lncurses -o /dev/null 2>/dev/null && echo yes)
ifneq ($(NCURSES_CHECK),yes)
$(error ncurses library not found. Please install libncurses-dev or ncurses-devel)
endif

# Default target
all: $(MCONF)

# Build mconf from sources
$(MCONF): $(MCONF_SRC)/mconf.c $(PARSER_SRC)/*.c $(LXDIALOG_SRC)/*.c
	@echo "  HOSTCC  $@"
	@$(HOSTCC) $(CFLAGS) -DLKC_DIRECT_LINK \
		$(MCONF_SRC)/mconf.c \
		$(PARSER_SRC)/confdata.c \
		$(PARSER_SRC)/expr.c \
		$(PARSER_SRC)/menu.c \
		$(PARSER_SRC)/symbol.c \
		$(PARSER_SRC)/util.c \
		$(LXDIALOG_SRC)/checklist.c \
		$(LXDIALOG_SRC)/inputbox.c \
		$(LXDIALOG_SRC)/menubox.c \
		$(LXDIALOG_SRC)/textbox.c \
		$(LXDIALOG_SRC)/util.c \
		$(LXDIALOG_SRC)/yesno.c \
		$(LDFLAGS) -o $@

clean:
	@rm -f $(MCONF) *.o

.PHONY: all clean
