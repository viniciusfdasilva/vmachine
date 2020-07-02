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
	#define INST_ADD_OPCODE   0x00
	#define INST_ADDI_OPCODE  0x08
	#define INST_ADDIU_OPCODE 0x09
	#define INST_ADDU_OPCODE  0x00
	#define INST_SUB_OPCODE   0x00
	#define INST_SUBU_OPCODE  0x00
	#define INST_MULT_OPCODE  0x00
	#define INST_MULTu_OPCODE 0x00
	#define INST_DIV_OPCODE   0x00
	#define INST_DIVU_OPCODE  0x00
	#define INST_AND_OPCODE   0x00
	#define INST_ANDI_OPCODE  0x0c
	#define INST_OR_OPCODE    0x00
	#define INST_ORI_OPCODE   0x0d
	#define INST_ORI_OPCODE   0x0d
	#define INST_XOR_OPCODE   0x00
	#define INST_XORI_OPCODE  0x0e
	#define INST_NOR_OPCODE   0x00
	#define INST_SLT_OPCODE   0x00
	#define INST_SLTI_OPCODE  0x0a
	#define INST_SLTIU_OPCODE 0x0b
	#define INST_SLTU_OPCODE  0x00
	#define INST_SLL_OPCODE   0x00
	#define INST_SRL_OPCODE   0x00
	#define INST_LW_OPCODE    0x23
	#define INST_SW_OPCODE    0x2b
	#define INST_BEQ_OPCODE   0x04
	#define INST_BNE_OPCODE   0x05
	#define INST_J_OPCODE     0x02
	#define INST_JR_OPCODE    0x00
	#define INST_JAL_OPCODE   0x03
	#define INST_LBU_OPCODE   0x24
	#define INST_LHU_OPCODE   0x25
	#define INST_LL_OPCODE    0x30
	#define INST_LUI_OPCODE   0x0f
	#define INST_SB_OPCODE    0x28
	#define INST_SC_OPCODE    0x38
	#define INST_SH_OPCODE    0x29
	#define INST_BCLT_OPCODE  0x11
	#define INST_BCLF_OPCODE  0x11
	#define INST_ADD.S_OPCODE 0x11
	#define INST_ADD.D_OPCODE 0x11
	#define INST_C.X.S_OPCODE 0x11
	#define INST_C.X.D_OPCODE 0x11
	#define INST_DIV.S_OPCODE 0x11
	#define INST_DIV.D_OPCODE 0x11
	#define INST_MUL.S_OPCODE 0x11
	#define INST_MUL.D_OPCODE 0x11
	#define INST_SUB.S_OPCODE 0x11
	#define INST_SUB.D_OPCODE 0x11
	#define INST_LWCL_OPCODE  0x31
	#define INST_LDCL_OPCODE  0x35
	#define INST_MFHI_OPCODE  0x00
	#define INST_MFLO_OPCODE  0x00
	#define INST_MFC0_OPCODE  0x10
	#define INST_SRA_OPCODE   0x00
	#define INST_SWCL_OPCODE  0x39
	#define INST_SDCL_OPCODE  0x3d
	/**@}*/

	/**
	 * @name Function of Instructions
	 */
	/**@{*/
	#define INST_ADD_FUNCT   0x20
	#define INST_ADDU_FUNCT  0x21
	#define INST_SUB_FUNCT   0x22
	#define INST_SUBU_FUNCT  0x23
	#define INST_MULT_FUNCT  0x18
	#define INST_MULTU_FUNCT 0x19
	#define INST_DIV_FUNCT   0x1a
	#define INST_DIVU_FUNCT  0x1b
	#define INST_AND_FUNCT   0x24
	#define INST_OR_FUNCT    0x25
	#define INST_XOR_FUNCT   0x26
	#define INST_NOR_FUNCT   0x27
	#define INST_SLT_FUNCT   0x2a
	#define INST_SLTU_FUNCT  0x2b
	#define INST_SLL_FUNCT   0x00
	#define INST_SRL_FUNCT   0x02
	#define INST_JR_FUNCT    0x08
	#define INST_MFHI_FUNCT  0x10
	#define INST_MFLO_FUNCT  0x12
	#define INST_SRA_FUNCT   0x03
	/**@#}*/

#endif /* ARCH_MIPS32_MACHINE_H_ */
