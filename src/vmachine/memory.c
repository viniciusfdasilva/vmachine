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
#include <stdlib.h>

/* Ours */
#include <vmachine.h>
#include <utils.h>

/**
 * @brief Memory.
 */
static word_t *memory = NULL;

/**
 * The memory_init() function intializes the underlying memory.
 */
void memory_init(void)
{
	memory = smalloc(MEMORY_SIZE);
}

/**
 * The memory_shutdown() function shutdowns the memory component.
 */
void memory_shutdown(void)
{
	/* Uninitialized memory. */
	if (memory == NULL)
		error("uninitialzied memory");

	free(memory);
}

/**
 * The memory_read() function reads a word from the memory.
 */
word_t memory_read(addr_t addr)
{
	if (addr >= MEMORY_SIZE)
		error("memory out of range");

	return (*(memory + (addr >> WORD_SIZE_LOG2)));
}

/**
 * The memory_write() function writes a word to the memory.
 */
void memory_write(addr_t addr, word_t word)
{
	if (addr >= MEMORY_SIZE)
		error("memory out of range");

	*(memory + (addr >> WORD_SIZE_LOG2)) = word;
}
