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

# Executable name
export EXEC = vmachine

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
export CXX := g++
export LD := g++

# Linker Options
export LDFLAGS :=

# Compiler Options
export CXXFLAGS += -std=c++11
export CXXFLAGS += -Wall -Wextra -Werror -Wa,--warn -Wfatal-errors
export CXXFLAGS += -Winit-self -Wswitch-default -Wfloat-equal
export CXXFLAGS += -Wundef -Wshadow -Wuninitialized
export CXXFLAGS += -Wvla  -Wredundant-decls
export CXXFLAGS += -Wno-unused-function
export CXXFLAGS += -I $(INCDIR)
ifeq ($(RELEASE), true)
export CXXFLAGS += -D NDEBUG -O3      # Optimize for Performance
else
export CXXFLAGS += -O0 -g             # Optimize for Debugging
endif

#===============================================================================

# Builds everything.
all:| make-dirs
	$(MAKE) -C $(SRCDIR) all

# Make directories
make-dirs: distclean
	@mkdir -p $(BINDIR)
	@mkdir -p $(LIBDIR)

# Cleans build.
clean:
	$(MAKE) -C $(SRCDIR) clean

# Cleans everything.
distclean:
	$(MAKE) -C $(SRCDIR) distclean

# Run.
run: all
	$(BINDIR)/$(EXEC)

# Builds documentation.
documentation:
	mkdir -p $(DOCDIR)
	doxygen doxygen/doxygen

