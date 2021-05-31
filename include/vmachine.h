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

#ifndef VMACHINE_H_
#define VMACHINE_H_

	// Theirs
	#include <string>
	#include <iostream>

	// Ours
	#include <vmachine/cache.h>
	#include <vmachine/core.h>
	#include <vmachine/isa.h>
	#include <vmachine/memory.h>
	#include <arch.h>

namespace vmachine
{
	/**
	 * @brief Virtual Machine
	 */
	class VMachine
	{
		private:

			/**
			 * @brief Start Address
			 */
			const isa32::word_t startAddr = 0;

			/**
			 * @group Memory System
			 */
			/**@{*/
			ICache &icache; /**< Instruction Cache */
			DCache &dcache; /**< Data Cache        */
			Memory &memory; /**< Main Memory       */
			/**@}*/

			/**
			 * @brief Core
			 */
			vmachine::Core core;

		public:

			/**
			 * @brief Default constructor.
			 */
			VMachine(
				ICache &icache_,
				DCache &dcache_,
				Memory &memory_
			) :
				icache(icache_),
				dcache(dcache_),
				memory(memory_),
				core(memory_)
			{ }

			/**
			 * @brief Loads an ASM file into the virtual machine.
			 *
			 * @param asmfile Target assembly file.
			 */
			void load(std::string &asmfile);

			/**
			 * @brief Loads an Flat-binary file into the virtual machine.
			 *
			 * @param flatBinaryFile Target assembly file.
			 */
			void loadFlatBinary(std::string &flatBinaryFile);

			/**
			 * @brief Starts the virtual machine.
			 */
			void start(void);

			/*
			 * @brief Loads a binary file into the virtual machine.
			 *
			 * @param binFile Target a binary file.
			 */
			void loadFile(std::string &binFile);

			/**
			 * @brief Executes a single instruction.
			 *
			 * @param inst Target instruction to execute.
			 */
			void execute(isa32::word_t inst) { core.execute(inst); }

			/**
			 * @brief Gets the value the program counter register.
			 */
			isa32::word_t getPC(void) { return (core.getPC()); }

			/**
			 * @brief Gets the value of a register.
			 *
			 * @param regnum Number of the target register.
			 */
			isa32::word_t getRegister(unsigned regnum) { return (core.getRegister(regnum)); }

			/**
			 * @brief Shutdowns the target virtual machine.
			 *
			 * @param outfile Output file where VM state should be dumped.
			 */
			void shutdown(std::ostream &outfile);
	};
}

#endif // VMACHINE_H_
