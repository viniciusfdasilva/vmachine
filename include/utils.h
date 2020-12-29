//
//  MIT License
//
// Copyright(c) 2011-2020 The Maintainers of Nanvix
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef UTILS_H_
#define UTILS_H_

	#include <string>

	/**
	 * @brief Converts an integer to a binary string.
	 *
	 * @param val Target value.
	 *
	 * @returns A pointer to the resulting string.
	 */
	extern std::string itoa2(int val);

    /**
	 * @brief Convert an string value in binary base to integer value in
	 * decimal base.
	 *
	 * @param str String value in binary base
	 * @return Value in decimal.
	 */
	extern int atoi2(std::string str);

	/**
	 * @brief Get substring of the a master string
	 *
	 * @param str Master string
	 * @param init Index
	 * @param Index
	 */
	extern std::string substring(std::string str,const unsigned int init,const unsigned int end);

    /**
	 * @brief Check if two string are equals
	 *
	 * @param str1
	 * @param str2
	 */
	extern bool equals(std::string str1,std::string str2);

	/**
	 * @brief Prints an error message and exits.
	 *
	 * @param msg Error message.
	 */
	extern void error(const std::string &msg);

#endif /* UTILS_H_ */
