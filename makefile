#
# MIT License
#
# Copyright(c) 2011-2020 The Maintainers of Nanvix
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

#
# Default make rule.
#
.DEFAULT_GOAL := all

#===============================================================================
# Build Options
#===============================================================================

# Verbose build?
export VERBOSE ?= no

# Release Version?
export RELEASE ?= no

# Installation Prefix
export PREFIX ?= $(HOME)

# Suppress self tests?
export SUPPRESS_TESTS ?= no

# Executable name
export EXEC=vmachine

#===============================================================================
# Directories
#===============================================================================

export ROOTDIR    := $(CURDIR)
export BINDIR     := $(ROOTDIR)/bin
export BUILDDIR   := $(ROOTDIR)/build
export CONTRIBDIR := $(ROOTDIR)/contrib
export DOCDIR     := $(ROOTDIR)/doc
export INCDIR     := $(ROOTDIR)/include
export LIBDIR     := $(ROOTDIR)/lib
export SRCDIR     := $(ROOTDIR)/src

#===============================================================================
# Toolchain Configuration
#===============================================================================

# Toolchain
export CC := gcc
export LD := gcc

# Compiler Options
export CFLAGS += -D_GNU_SOURCE -D_POSIX_C_SOURCE=200112L
export CFLAGS += -Wno-error=pedantic

# Linker Options
export LDFLAGS :=

# Compiler Options
export CFLAGS += -std=c99 -fno-builtin
export CFLAGS += -Wall -Wextra -Werror -Wa,--warn
export CFLAGS += -Winit-self -Wswitch-default -Wfloat-equal
export CFLAGS += -Wundef -Wshadow -Wuninitialized
export CFLAGS += -Wvla  -Wredundant-decls
export CFLAGS += -Wno-unused-function
export CFLAGS += -I $(INCDIR)
ifeq ($(RELEASE), true)
export CFLAGS += -D NDEBUG -O3      # Optimize for Performance
else
export CFLAGS += -O0 -g             # Optimize for Debugging
export CFLAGS += -g
endif
ifeq ($(SUPPRESS_TESTS), true)
export CFLAGS += -D __SUPPRESS_TESTS
endif

#===============================================================================

# Builds everything.
all: | make-dirs
	$(MAKE) -C $(SRCDIR) all

# Make directories
make-dirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(LIBDIR)

# Cleans build.
clean:
	$(MAKE) -C $(SRCDIR) clean

# Cleans everything.
distclean:
	$(MAKE) -C $(SRCDIR) distclean

# Builds documentation.
documentation:
	mkdir -p $(DOCDIR)
	doxygen doxygen/doxygen
