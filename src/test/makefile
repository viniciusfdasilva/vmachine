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

#===============================================================================
# Sources
#===============================================================================

# Source Files
SRC = $(wildcard $(CURDIR)/assembler/*.c)
SRC = $(wildcard $(CURDIR)/vmachine/*.c)

#===============================================================================
# Object Files
#===============================================================================

OBJ = $(SRC:.c=.o)

#===============================================================================

# Builds all object files.
all: $(OBJ)
ifeq ($(VERBOSE), no)
	@echo [LD] $(EXEC)
	@$(LD) $(LDFLAGS) $(OBJ) -o $(BINDIR)/$(EXEC)
else
	$(LD) $(LDFLAGS) $(OBJ) -o $(BINDIR)/$(EXEC)
endif

# Cleans all object files.
clean:
ifeq ($(VERBOSE), no)
	@echo [CLEAN] $(OBJ)
	@rm -rf $(OBJ)
else
	rm -rf $(OBJ)
endif

# Cleans everything.
distclean: clean
ifeq ($(VERBOSE), no)
	@echo [CLEAN] $(EXEC)
	@rm -rf $(BINDIR)/$(EXEC)
else
	rm -rf $(LIBDIR)/$(LIBHAL)
endif

# builds a C source file.
%.o: %.c
ifeq ($(VERBOSE), no)
	@echo [CC] $@
	@$(CC) $(CFLAGS) $< -c -o $@
else
	$(CC) $(CFLAGS) $< -c -o $@
endif
