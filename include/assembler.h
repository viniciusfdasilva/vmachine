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

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

// Theirs
#include <iostream>

// Ours
#include <arch.h>

/**
 * @brief Assembler
 */
class Assembler
{
	private:

		const char *delim = " ,()";

	public:

		/**
		 * @brief Assembles a source file.
		 *
		 * @param file Stream to target input file.
		 */
		void assembly(std::istream &input);

		/**
		 * @brief Assembles a command.
		 *
		 * @param line Command line.
		 *
		 * @returns The encoded instruction.
		 */
		isa32::word_t assembly(std::string &line);

		/**
		 * @brief Encodes a instruction.
		 */
		virtual isa32::word_t encode_instruction(const std::vector<const char *> &inst) = 0;
};

#endif /* ASSEMBLER_H_ */