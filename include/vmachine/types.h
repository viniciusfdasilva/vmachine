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

#ifndef VMACHINE_TYPES_H_
#define VMACHINE_TYPES_H_

	/* External */
	#include <stdint.h>

	/**
	 * @brief Sizes for Machine Types (in bytes)
	 */
	/**@{*/
	#define WORD_SIZE_LOG2 2                /**< log2(Word ) */
	#define WORD_SIZE (1 << WORD_SIZE_LOG2) /**< Word        */
	/**@}*/

	/**
	 * @name Machine Types
	 */
	/**@{*/
	typedef uint32_t addr_t;  /**< Address    */
	typedef uint16_t hword_t; /**< Half-Word   */
	typedef uint32_t word_t;  /**< Word        */
	typedef uint64_t dword_t; /**< Double-Word */
	/**@}*/

#endif /* VMACHINE_TYPES_H_ */
