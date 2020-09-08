/*
 * MIT License
 *
 * Copyright(c) 2011-2020 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


/* External */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

/* Ours */
#include <vmachine.h>
#include <utils.h>
#include <asm.h>

/**
 * @brief Loads an assembly file.
 */
void load_asmfile(const char *filename, addr_t addr)
{
	FILE *input;                       /* Input File              */
	const char *errorstr;              /* Error String            */
	static const char *delim = " ,()"; /* Delimitating characters */

	ssize_t nread;
	size_t len = 0;
	char *line = NULL;

	/* Cannot open input file. */
	if ((input = fopen(filename, "r")) == NULL)
	{
		errorstr = "cannot open asm file";
		error(errorstr);
	}

	/* Read input file. */
	while ((nread = getline(&line, &len, input)) != -1)
	{
		char *token;
		uint32_t instruction;

		/* Remove newline. */
		line[nread - 1] = '\0';

		/* Parse line. */
		debug(line);
		if ((token = strtok(line, delim)) == NULL)
			break;

		instruction = assembler(line);

		memory_write(addr, instruction);
		addr += WORD_SIZE;
	}

	/* House keeping. */
	free(line);
}

/**
 * The load() function loads the memory of the virtual machine with the
 * contents of the file named @p filename.
 */
void load(const char *filename, addr_t addr)
{
	load_asmfile(filename, addr);
}
