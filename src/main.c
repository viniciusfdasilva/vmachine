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

#include <stdio.h>
#include <stdlib.h>
#include <vmachine.h>
#include "test_mips32.h"

/**
 * @brief Command Line Arguments
 */
struct
{
	const char *filename; /**< Name of Input File */
} args;

/**
 * @brief Prints program usage and exits.
 */
static void usage(void)
{
	printf("usage: vmachine input [options]\n");
	exit(EXIT_SUCCESS);
}

/**
 * @brief Parses command line arguments.
 *
 * @param argc Argument count.
 * @param argv Argument list.
 */
void args_parse(int argc, const char *argv[])
{
	/* Missing input file. */
	if (argc < 2)
	{
		printf("missing input file\n");
		usage();
	}

	args.filename = argv[1];
}

/**
 * @brief Simulates a manycore processor.
 */
int main(int argc, const char *argv[])
{
	((void) argc);
	((void) argv);
	test_mips32();

	args_parse(argc, argv);

	vmachine_start(args.filename);

	return (EXIT_SUCCESS);
}
