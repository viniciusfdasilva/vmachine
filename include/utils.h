/*
 * MIT License
 *
 * Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
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


#ifndef UTILS_H_
#define UTILS_H_

	#include <stddef.h>
	#include <stdbool.h>

	/**
	 * @brief Prints an error message and exits.
	 *
	 * @param msg Error message.
	 */
	extern void error(const char *msg);

	/**
	 * @brief Prints a debug message.
	 *
	 * @param msg Debug message.
	 */
	extern void  debug(const char *msg);

	/**
	 * @brief Converts an integer to a binary string.
	 *
	 * @param val Target value.
	 * @param str Target buffer to store resulting string.
	 *
	 * @returns A pointer to the resulting string.
	 */
	extern char *itoa2(int val, char *str, int base2);

	/**
	 * @brief Make pow of two intergers numbers
	 * @param x Base
	 * @param y Power positive
	 * @return Wattage value
	 */
	extern int pow2(int x,int y);

	/**
	 * @brief Convert an string value in binary base 
	 * to integer value in decimal base. 
	 * @param str String value in binary base
	 * @return Value in decimal.
	 */
	extern int atoi2(char* str);
	
	/**
	 * @brief Get substring of the a master string
	 * @param str Master string
	 * @param init Index
	 * @param Index
	 */
	extern char* substring(const char* str,const int init,const int end);

	/**
	 * @brief Concat string set
	 * @param string_set[] Set of strings
	 * @param buff Master buffer
	 */
	extern void concat(char *string_set[],unsigned int length,char* buff);
	/**
	 * @brief Check if two string are equals
	 * @param str1
	 * @param str2
	 */
	extern bool equals(const char* str1,const char* str2);

	/**
	 * @brief Asserts a condition.
	 *
	 * @param x        Target condition.
	 * @param msg      Assert message.
	 * @param filename File name.
	 * @param linenum  Line number.
	 */
	extern void __checkfail(int x, const char *msg, const char *filename, int linenum);

	/**
	 * @brief Safe malloc()
	 *
	 * @param n Number of bytes to allocate.
	 *
	 * @returns The allocated memory block area. If any error occurs, the
	 * program panics.
	 */
	extern void *smalloc(size_t n);

	/**
	 * @see _check()
	 */
	#ifdef NDEBUG
	#define _check(x, msg) { ((void)(x)); ((void)(msg)); }
	#else
	#define _check(x, msg) __checkfail(x, msg, __FILE__, __LINE__)
	#endif

	/**
	 * @brief Asserts a condition.
	 *
	 * @param x Target condition.
	 */
	#define check(x) _check(x, "assert() failed")

#endif /* UTILS_H_ */
