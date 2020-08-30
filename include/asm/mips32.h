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

#ifndef ASM_MIPS32_H_
#define ASM_MIPS32_H_

// Theirs.
#include <vector>

// Ours
#include <assembler.h>

/**
 * @brief MIPS-32
 */
namespace mips32
{
	/**
	 * @name Name of Registers
	 */
	/**@{*/
	#define REG_NAME_ZERO "zero"
	#define REG_NAME_AT   "at"
	#define REG_NAME_V0   "v0"
	#define REG_NAME_V1   "v1"
	#define REG_NAME_A0   "a0"
	#define REG_NAME_A1   "a1"
	#define REG_NAME_A2   "a2"
	#define REG_NAME_A3   "a3"
	#define REG_NAME_T0   "t0"
	#define REG_NAME_T1   "t1"
	#define REG_NAME_T2   "t2"
	#define REG_NAME_T3   "t3"
	#define REG_NAME_T4   "t4"
	#define REG_NAME_T5   "t5"
	#define REG_NAME_T6   "t6"
	#define REG_NAME_T7   "t7"
	#define REG_NAME_S0   "s0"
	#define REG_NAME_S1   "s1"
	#define REG_NAME_S2   "s2"
	#define REG_NAME_S3   "s3"
	#define REG_NAME_S4   "s4"
	#define REG_NAME_S5   "s5"
	#define REG_NAME_S6   "s6"
	#define REG_NAME_S7   "s7"
	#define REG_NAME_T8   "t8"
	#define REG_NAME_T9   "t9"
	#define REG_NAME_K0   "k0"
	#define REG_NAME_K1   "k1"
	#define REG_NAME_GP   "gp"
	#define REG_NAME_SP   "sp"
	#define REG_NAME_FP   "fp"
	#define REG_NAME_RA   "ra"
	/**@{*/

	/**
	 * @name Name of Instructions
	 */
	/**@{*/
	#define INST_NAME_ADD  "add"
	#define INST_NAME_ADDI "addi"
	#define INST_NAME_SUB  "sub"
	#define INST_NAME_MULT "mult"
	#define INST_NAME_DIV  "div"
	#define INST_NAME_AND  "and"
	#define INST_NAME_ANDI "andi"
	#define INST_NAME_OR   "or"
	#define INST_NAME_ORI  "ori"
	#define INST_NAME_XOR  "xor"
	#define INST_NAME_NOR  "nor"
	#define INST_NAME_SLT  "slt"
	#define INST_NAME_SLTI "slti"
	#define INST_NAME_SLL  "sll"
	#define INST_NAME_SRL  "srl"
	#define INST_NAME_LW   "lw"
	#define INST_NAME_SW   "sw"
	#define INST_NAME_BEQ  "beq"
	#define INST_NAME_BNE  "bne"
	#define INST_NAME_J    "j"
	#define INST_NAME_JR   "jr"
	#define INST_NAME_JAL  "jal"
	/**@}*/

	/**
	 * @brief MIPS-32 Assembler
	 */
	class Mips32Assembler : public Assembler
	{
		public:

			/**
			 * @brief Encodes an instruction.
			 *
			 * @param inst Tokenized instruction.
			 *
			 * @param The machine code for the target instruction.
			 */
			isa32::word_t encode_instruction(const std::vector<const char *> &inst) override;
	};
}

#endif // ASM_MIPS32_H_