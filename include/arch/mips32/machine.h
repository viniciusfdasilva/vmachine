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

#ifndef ARCH_MIPS32_MACHINE_H_
#define ARCH_MIPS32_MACHINE_H_

	/**
	 * @name Operation Codes of Instructions
	 */
	/**@{*/
	#define INST_ADD_OPCODE  0x00
	#define INST_ADDI_OPCODE 0x08
	#define INST_SUB_OPCODE  0x00
	#define INST_MULT_OPCODE 0x00
	#define INST_DIV_OPCODE  0x00
	#define INST_AND_OPCODE  0x00
	#define INST_ANDI_OPCODE 0x0c
	#define INST_OR_OPCODE   0x00
	#define INST_ORI_OPCODE  0x0d
	#define INST_XOR_OPCODE  0x00
	#define INST_NOR_OPCODE  0x00
	#define INST_SLT_OPCODE  0x00
	#define INST_SLTI_OPCODE 0x0a
	#define INST_SLL_OPCODE  0x00
	#define INST_SRL_OPCODE  0x00
	#define INST_LW_OPCODE   0x23
	#define INST_SW_OPCODE   0x2b
	#define INST_BEQ_OPCODE  0x04
	#define INST_BNE_OPCODE  0x05
	#define INST_J_OPCODE    0x02
	#define INST_JR_OPCODE   0x00
	#define INST_JAL_OPCODE  0x03
	/**@}*/

	/**
	 * @name Function of Instructions
	 */
	/**@{*/
	#define INST_ADD_FUNCT  0x20
	#define INST_SUB_FUNCT  0x22
	#define INST_MULT_FUNCT 0x18
	#define INST_DIV_FUNCT  0x1a
	#define INST_AND_FUNCT  0x24
	#define INST_OR_FUNCT   0x25
	#define INST_XOR_FUNCT  0x26
	#define INST_NOR_FUNCT  0x27
	#define INST_SLT_FUNCT  0x2a
	#define INST_SLL_FUNCT  0x00
	#define INST_SRL_FUNCT  0x02
	#define INST_JR_FUNCT   0x08
	/**@#}*/

#endif /* ARCH_MIPS32_MACHINE_H_ */
