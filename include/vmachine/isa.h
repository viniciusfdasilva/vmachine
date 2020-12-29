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
	#define INST_SHIFT_FUNCT_7          0X18
	#define INST_SHIFT_RS_1             0x0c
	#define INST_SHIFT_RS_2             0x14
	#define INST_SHIFT_FUNCT_3          0x0c
	#define INST_SHIFT_RD               0x04
	#define INST_SHIFT_IMMEDIATE_I_TYPE 0x14
	#define INST_SHIFT_IMMEDIATE        0x0c
	/**@}*/

	/**
	 * @name Masks for Instruction Fields
	 */
	/**@{*/
	#define INST_MASK_FUNCT_7           0xfe000000
	#define INST_MASK_RS_1              0x000f8000
	#define INST_MASK_RS_2              0x01f00000
	#define INST_MASK_FUNCT_3           0x00007000
	#define INST_MASK_RD                0x00000f80
	#define INST_MASK_OPCODE            0x0000007f
	#define INST_MASK_IMMEDIATE_I_TYPE  0xfff00000
	#define INST_MASK_IMMEDIATE         0xfffff000
	/**@}*/

	/**
	 * @name Operation Codes of Instructions
	 */
	/**@{*/

	/* Instructions Opcodes Division */
	#define U_TYPE_IMMEDIATE_INSTRUCTION            0x37
	#define U_TYPE_PC_INSTRUCTION                   0x17
	#define J_TYPE_INSTRUCTION                      0x6f
	#define I_TYPE_JUMPER_INSTRUCTION               0x67
	#define I_TYPE_LOAD_INSTRUCTIONS                0x03
	#define I_TYPE_REGISTERS_INSTRUCTIONS           0x13
	#define I_TYPE_FENCE_INSTRUCTIONS               0x0f
	#define I_TYPE_CALL_BREAKPOINT_CRS_INSTRUCTIONS 0x73
	#define B_TYPE_INSTRUCTIONS                     0x63
	#define S_TYPE_INSTRUCTIONS                     0x23
	#define R_TYPE_INSTRUCTIONS                     0x33

	/* U-Type */
	#define INST_OPCODE_LUI   0x37
	#define INST_OPCODE_AUIPC 0x17

	/* J-TYPE */
	#define INST_OPCODE_JAL 0x6f

	/* I-Type */
	#define INST_OPCODE_JALR    0x67
	#define INST_OPCODE_LB      0x03
	#define INST_OPCODE_LH      0x03
	#define INST_OPCODE_LW      0x03
	#define INST_OPCODE_LBU     0x03
	#define INST_OPCODE_LHU     0x03
	#define INST_OPCODE_ADDI    0x13
	#define INST_OPCODE_SLTI    0x13
	#define INST_OPCODE_SLTIU   0x13
	#define INST_OPCODE_XORI    0x13
	#define INST_OPCODE_ORI     0x13
	#define INST_OPCODE_ANDI    0x13
	#define INST_OPCODE_SLLI    0x13
	#define INST_OPCODE_SRLI    0x13
	#define INST_OPCODE_SRAI    0x13
	#define INST_OPCODE_FENCE   0x0f
	#define INST_OPCODE_FENCE_I 0x0f
	#define INST_OPCODE_ECALL   0x73
	#define INST_OPCODE_EBREAK  0x73
	#define INST_OPCODE_CSRRW   0x73
	#define INST_OPCODE_CSRRS   0x73
	#define INST_OPCODE_CSRRC   0x73
	#define INST_OPCODE_CSRRWI  0x73
	#define INST_OPCODE_CSRRSI  0x73
	#define INST_OPCODE_CSRRCI  0x73

	/**
	 * @name Function 3 of Instructions
	 */
	/**@{*/

	/* R-Type */
	#define INST_ADD_SUB_FUNCT_3 0x00
	#define INST_SLL_FUNCT_3     0x01
	#define INST_SLT_FUNCT_3     0x02
	#define INST_SLTU_FUNCT_3    0x03
	#define INST_XOR_FUNCT_3     0x04
	#define INST_SRL_SRA_FUNCT_3 0x05
	#define INST_OR_FUNCT_3      0x06
	#define INST_AND_FUNCT_3     0x07

	/* I_Type */
	#define INST_JALR_FUNCT_3    0x00
	#define INST_LB_FUNCT_3      0x00
	#define INST_LH_FUNCT_3      0x01
	#define INST_LW_FUNCT_3      0x02
	#define INST_LBU_FUNCT_3     0x04
	#define INST_LHU_FUNCT_3     0x05
	#define INST_ADDI_FUNCT_3    0x00
	#define INST_SLTI_FUNCT_3    0x02
	#define INST_SLTIU_FUNCT_3   0x03
	#define INST_XORI_FUNCT_3    0x04
	#define INST_ORI_FUNCT_3     0x06
	#define INST_ANDI_FUNCT_3    0x07
	#define INST_SLLI_FUNCT_3    0x01
	#define INST_SRLI_FUNCT_3    0x05
	#define INST_SRAI_FUNCT_3    0x05
	#define INST_FENCE_FUNCT_3   0x00
	#define INST_FENCE_I_FUNCT_3 0x01
	#define INST_ECALL_FUNCT_3   0x00
	#define INST_EBREAK_FUNCT_3  0x00
	#define INST_CSRRW_FUNCT_3   0x01
	#define INST_CSRRS_FUNCT_3   0x02
	#define INST_CSRRC_FUNCT_3   0x03
	#define INST_CSRRWI_FUNCT_3  0x05
	#define INST_CSRRSI_FUNCT_3  0x06
	#define INST_CSRRCI_FUNCT_3  0x07

	/* B-Type*/
	#define INST_BEQ_FUNCT_3  0x00
	#define INST_BNE_FUNCT_3  0x01
	#define INST_BLT_FUNCT_3  0x04
	#define INST_BGE_FUNCT_3  0x05
	#define INST_BLTU_FUNCT_3 0x06
	#define INST_BGEU_FUNCT_3 0x07

	/* S-Type */
	#define INST_SB_FUNCT_3 0x00
	#define INST_SH_FUNCT_3 0x01
	#define INST_SW_FUNCT_3 0x02
	/**@#}*/

	/**
	 * @name Function 7 of Instructions
	 */
	/**@{*/
	#define INST_ADD_FUNCT_7  0x00
	#define INST_SUB_FUNCT_7  0x20
	#define INST_SLL_FUNCT_7  0x00
	#define INST_SLT_FUNCT_7  0x00
	#define INST_SLTU_FUNCT_7 0x00
	#define INST_XOR_FUNCT_7  0x00
	#define INST_SRL_FUNCT_7  0x00
	#define INST_SRA_FUNCT_7  0x20
	#define INST_OR_FUNCT_7   0x00
	#define INST_AND_FUNCT_7  0x00
	/**@#}*/

	/**@}*/
};

#endif // VMACHINE_ISA_H_
