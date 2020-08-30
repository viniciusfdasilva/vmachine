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

#ifndef ARCH_MIPS32_H_
#define ARCH_MIPS32_H_

/**
 * @brief MIPS 32-Bit
 */
namespace mips32
{
	/**
	 * @name Code of Registers
	 */
	/**@{*/
	#define REG_ZERO  0x00
	#define REG_AT    0x01
	#define REG_V0    0x02
	#define REG_V1    0x03
	#define REG_A0    0x04
	#define REG_A1    0x05
	#define REG_A2    0x06
	#define REG_A3    0x07
	#define REG_T0    0x08
	#define REG_T1    0x09
	#define REG_T2    0x0a
	#define REG_T3    0x0b
	#define REG_T4    0x0c
	#define REG_T5    0x0d
	#define REG_T6    0x0e
	#define REG_T7    0x0f
	#define REG_S0    0x10
	#define REG_S1    0x11
	#define REG_S2    0x12
	#define REG_S3    0x13
	#define REG_S4    0x14
	#define REG_S5    0x15
	#define REG_S6    0x16
	#define REG_S7    0x17
	#define REG_T8    0x18
	#define REG_T9    0x19
	#define REG_K0    0x1a
	#define REG_K1    0x1b
	#define REG_GP    0x1c
	#define REG_SP    0x1d
	#define REG_FP    0x1e
	#define REG_RA    0x1f
	/**@}*/

	/**
	 * @name Shifts for Instruction Fields
	 */
	/**@{*/
	#define INST_SHIFT_IMM     0
	#define INST_SHIFT_TARGET  0
	#define INST_SHIFT_FUNCT   0
	#define INST_SHIFT_SHAMT   6
	#define INST_SHIFT_RD     11
	#define INST_SHIFT_RT     16
	#define INST_SHIFT_RS     21
	#define INST_SHIFT_OPCODE 26
	/**@}*/

	/**
	 * @name Masks for Instruction Fields
	 */
	/**@{*/
	#define INST_MASK_IMM    0x000ffff
	#define INST_MASK_TARGET 0x3ffffff
	#define INST_MASK_FUNCT  0x000003f
	#define INST_MASK_SHAMT  0x000001f
	#define INST_MASK_RD     0x000001f
	#define INST_MASK_RT     0x000001f
	#define INST_MASK_RS     0x000001f
	#define INST_MASK_OPCODE 0x000003f
	/**@}*/

	/**
	 * @name Operation Codes of Instructions
	 */
	/**@{*/
	#define INST_OPCODE_ADD  0x00
	#define INST_OPCODE_ADDI 0x08
	#define INST_OPCODE_SUB  0x00
	#define INST_OPCODE_MULT 0x00
	#define INST_OPCODE_DIV  0x00
	#define INST_OPCODE_AND  0x00
	#define INST_OPCODE_ANDI 0x0c
	#define INST_OPCODE_OR   0x00
	#define INST_OPCODE_ORI  0x0d
	#define INST_OPCODE_XOR  0x00
	#define INST_OPCODE_NOR  0x00
	#define INST_OPCODE_SLT  0x00
	#define INST_OPCODE_SLTI 0x0a
	#define INST_OPCODE_SLL  0x00
	#define INST_OPCODE_SRL  0x00
	#define INST_OPCODE_LW   0x23
	#define INST_OPCODE_SW   0x2b
	#define INST_OPCODE_BEQ  0x04
	#define INST_OPCODE_BNE  0x05
	#define INST_OPCODE_J    0x02
	#define INST_OPCODE_JR   0x00
	#define INST_OPCODE_JAL  0x03
	#define INST_OPCODE_NONE 0x3f
	/**@{*/

	/**
	 * @brief Function of Instructions
	 */
	/**@{*/
	#define INST_FUNCT_ADD  0x20
	#define INST_FUNCT_SUB  0x22
	#define INST_FUNCT_MULT 0x18
	#define INST_FUNCT_DIV  0x1a
	#define INST_FUNCT_AND  0x24
	#define INST_FUNCT_OR   0x25
	#define INST_FUNCT_XOR  0x26
	#define INST_FUNCT_NOR  0x27
	#define INST_FUNCT_SLT  0x2a
	#define INST_FUNCT_SLL  0x00
	#define INST_FUNCT_SRL  0x02
	#define INST_FUNCT_JR   0x08
	#define INST_FUNCT_NONE 0x1f
	/**@}*/
}

#endif /* ARCH_MIPS32_H_  */