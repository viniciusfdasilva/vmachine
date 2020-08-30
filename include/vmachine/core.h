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

#ifndef VMACHINE_CORE_H_
#define VMACHINE_CORE_H_

    #include <vmachine/memory.h>
    #include <arch.h>

namespace vmachine
{
    #define REGISTERS_NUMS 32

    /**
     * @brief 32-bit Core
     */
    class Core
    {
        private:

            Memory &memory_;

            typedef void (Core::*execute_fn)(isa32::word_t);

            /**
             * @brief Program Counter
             */
            isa32::word_t pc = 0;

            /**
             * @brief General Purpose Registers
             */
            isa32::word_t regs[REGISTERS_NUMS] = { 0 };

            /**
             * @brief Mult/Div Registers
             */
            /**@{*/
            isa32::word_t lo;
            isa32::word_t hi;
            /**@}*/

            /**
             * @brief Fetches an instruction.
             * 
             * @returns The fetched instruction.
             */
            isa32::word_t fetch(void);

            /**
             * @brief Decodes an instruction.
             * 
             * @param inst Target instruction.
             */
            execute_fn decode(isa32::word_t inst);

            /**
             * @brief Executes a R-Type Instruction
             * 
             * @param inst Target instruction.
             */
            void executeR(isa32::word_t inst);

            /**
             * @brief Executes a I-Type Instruction
             * 
             * @param inst Target instruction.
             */
            void executeI(isa32::word_t inst);

            /**
             * @brief Executes a J-Type Jnstruction
             * 
             * @param inst Target instruction.
             */
            void executeJ(isa32::word_t inst);

        public:

            /**
             * @brief Default constructor.
             */
            Core(Memory &memory) : memory_(memory) { }

            /**
             * @brief Runs the target core.
             */
            void run(void);

            /**
             * @brief Executes a single instruction.
             */
            void execute(isa32::word_t inst);

			/**
			 * @brief Gets the value the program counter register.
			 */
			isa32::word_t getPC(void) { return (pc); }

			/**
			 * @brief Gets the value of a register.
			 * 
			 * @param regnum Number of the target register.
			 */
			isa32::word_t getRegister(unsigned regnum) { return (regs[regnum]); }
    };
}

#endif // VMACHINE_CORE_H_