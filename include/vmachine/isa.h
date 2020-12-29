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

#ifndef VMACHINE_ISA_H_
#define VMACHINE_ISA_H_

namespace vmachine
{
	/**
	 * @name Code of Registers
	 */
	/**@{*/
	#define REG_0  0x00
	#define REG_1  0x01
	#define REG_2  0x02
	#define REG_3  0x03
	#define REG_4  0x04
	#define REG_5  0x05
	#define REG_6  0x06
	#define REG_7  0x07
	#define REG_8  0x08
	#define REG_9  0x09
	#define REG_10 0x0a
	#define REG_11 0x0b
	#define REG_12 0x0c
	#define REG_13 0x0d
	#define REG_14 0x0e
	#define REG_15 0x0f
	#define REG_16 0x10
	#define REG_17 0x11
	#define REG_18 0x12
	#define REG_19 0x13
	#define REG_20 0x14
	#define REG_21 0x15
	#define REG_22 0x16
	#define REG_23 0x17
	#define REG_24 0x18
	#define REG_25 0x19
	#define REG_26 0x1a
	#define REG_27 0x1b
	#define REG_28 0x1c
	#define REG_29 0x1d
	#define REG_30 0x1e
	#define REG_31 0x1f
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
	
	/* R-TYPE */
	#define INST_OPCODE_ADD   0x00
	#define INST_OPCODE_ADDU  0x00
	#define INST_OPCODE_AND   0x00
	#define INST_OPCODE_NOR   0x00
	#define INST_OPCODE_OR    0x00
	#define INST_OPCODE_SLT   0x00
	#define INST_OPCODE_SLTU  0x00		
	#define INST_OPCODE_SUB   0x00
	#define INST_OPCODE_SUBU  0x00
	#define INST_OPCODE_XOR   0x00
	#define INST_OPCODE_JR    0x00
	#define INST_OPCODE_SLL   0x00
	#define INST_OPCODE_SRL   0x00
	#define INST_OPCODE_DIV   0x00
	#define INST_OPCODE_DIVU  0x00
	#define INST_OPCODE_MFHI  0x00
	#define INST_OPCODE_MFLO  0x00
	#define INST_OPCODE_MULT  0x00
	#define INST_OPCODE_MULTU 0x00
	#define INST_OPCODE_SRA   0x00
	
	/* I-TYPE */
	#define INST_OPCODE_ADDI  0x08
	#define INST_OPCODE_ADDIU 0x09
	#define INST_OPCODE_ANDI  0x0c
	#define INST_OPCODE_BEQ   0x04
	#define INST_OPCODE_BNE   0x05
	#define INST_OPCODE_LBU   0x24
	#define INST_OPCODE_LHU   0x25
	#define INST_OPCODE_LL    0x30
	#define INST_OPCODE_LUI   0x0f
	#define INST_OPCODE_LW    0x23
	#define INST_OPCODE_ORI   0x0d
	#define INST_OPCODE_SLTI  0x0a
	#define INST_OPCODE_SLTIU 0x0b
	#define INST_OPCODE_SB    0x28
	#define INST_OPCODE_SC    0x38
	#define INST_OPCODE_SH    0x29
	#define INST_OPCODE_SW    0x2b
	#define INST_OPCODE_XORI  0x0e		
		
	/* J-TYPE */
	#define INST_OPCODE_J     0x02
	#define INST_OPCODE_JAL   0x03

	/**
	 * @name Function of Instructions
	 */
	/**@{*/
	#define INST_FUNCT_ADD   0x20
	#define INST_FUNCT_ADDU  0x21
	#define INST_FUNCT_AND   0x24
	#define INST_FUNCT_NOR   0x27
	#define INST_FUNCT_OR    0x25
	#define INST_FUNCT_SLT   0x2a
	#define INST_FUNCT_SLTU  0x2b
	#define INST_FUNCT_SUB   0x22
	#define INST_FUNCT_SUBU  0x23
	#define INST_FUNCT_XOR   0x26
	#define INST_FUNCT_JR    0x08
	#define INST_FUNCT_SLL   0x00
	#define INST_FUNCT_SRL   0x02
	#define INST_FUNCT_DIV   0x1a
	#define INST_FUNCT_DIVU  0x1b
	#define INST_FUNCT_MFHI  0x10
	#define INST_FUNCT_MFLO  0x12
	#define INST_FUNCT_MULT  0x18
	#define INST_FUNCT_MULTU 0x19
	#define INST_FUNCT_SRA   0x03
	/**@#}*/
	
	/**@}*/
};

#endif // VMACHINE_ISA_H_
