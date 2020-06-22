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

#include <vmachine/cache.h>
uint32_t pc;

/**
 * @brief Fetches an instruction.
 */
void do_fetch(void)
{
	uint32_t instruction;

	instruction = icache_read(pc);
	pc += 4;
	
	return (instruction);
}

/**
 * @brief Executes an instruction.
 */
void do_execute(uint32_t instruction)
{
	/* TODO */
}

/**
 * @brief Handles Interrupts
 */
void do_interrupts(void)
{
	/* TODO */
}

/**
 * The core_init() initializes a core.
 */
void core_init(void)
{
	cache_init();
}

/**
 * The core_run() function runs a core.
 */
void core_run(void)
{
	while (1)
	{
		do_fetch();
		do_execute();

		do_interrupts();
	}
}
