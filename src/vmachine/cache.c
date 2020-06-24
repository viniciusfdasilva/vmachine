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

/* Ours */
#include <vmachine.h>

/**
 * The icache_read() function reads a word from the instruction cache.
 * The word is read from the address specified by @p addr.
 */
word_t icache_read(addr_t addr)
{
	word_t instruction;

	instruction = memory_read(addr);
	instruction = engine_run(instruction);

	return (instruction);
}

/**
 * The dcache_read() function reads a word from the data cache. The word
 * is read from the address specified by @p addr.
 */
word_t dcache_read(addr_t addr)
{
	word_t word;

	word = memory_read(addr);

	return (word);
}

/**
 * The dcache_write() function writes a word to the data cache. The word
 * is written at the address specified by @p addr.
 */
void dcache_write(addr_t addr, word_t data)
{
	memory_write(addr, data);
}

/**
 * @brief Initializes the cache.
 */
void cache_init(void)
{
	/* TODO */
}
