/*
 * MIT License
 *
 * Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
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

#ifndef MIPS32_INST_H_
#define MIPS32_INST_H_

	#include <stdio.h>

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
	 * @name Operation Codes of Instructions (in binary)
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
	 * @name Operation Codes of Instructions (as string)
	 */
	/**@{*/
	#define INST_ADD_OPCODE_STR  "000000"
	#define INST_ADDI_OPCODE_STR "001000"
	#define INST_SUB_OPCODE_STR  "000000"
	#define INST_MULT_OPCODE_STR "000000"
	#define INST_DIV_OPCODE_STR  "000000"
	#define INST_AND_OPCODE_STR  "000000"
	#define INST_ANDI_OPCODE_STR "001100"
	#define INST_OR_OPCODE_STR   "000000"
	#define INST_ORI_OPCODE_STR  "001101"
	#define INST_XOR_OPCODE_STR  "000000"
	#define INST_NOR_OPCODE_STR  "000000"
	#define INST_SLT_OPCODE_STR  "000000"
	#define INST_SLTI_OPCODE_STR "001010"
	#define INST_SLL_OPCODE_STR  "000000"
	#define INST_SRL_OPCODE_STR  "000000"
	#define INST_LW_OPCODE_STR   "100011"
	#define INST_SW_OPCODE_STR   "101011"
	#define INST_BEQ_OPCODE_STR  "000100"
	#define INST_BNE_OPCODE_STR  "000101"
	#define INST_J_OPCODE_STR    "000010"
	#define INST_JR_OPCODE_STR   "000000"
	#define INST_JAL_OPCODE_STR  "000011"
	/**@{*/

	/**
	 * @name Function of Instructions (in binary)
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
	#define INST_SLTU_FUNCT  0x2B
	#define INST_SLL_FUNCT   0x00
	#define INST_SRL_FUNCT   0x02
	#define INST_SRA_FUNCT   0x03
	#define INST_JR_FUNCT    0x08
	/**@#}*/

	/**
	 * @name Function Code of Instructions (as string)
	 */
	/**@{*/
	#define INST_ADD_FUNCT_STR   "100000"
	#define INST_ADDU_FUNCT_STR  "100001"
	#define INST_SUB_FUNCT_STR   "100010"
	#define INST_SUBU_FUNCT_STR  "100011"
	#define INST_MULT_FUNCT_STR  "011000"
	#define INST_SLTU_FUNCT_STR  "101011"
	#define INST_SRA_FUNCT_STR   "000011"
	#define INST_MULTU_FUNCT_STR "011001"
	#define INST_DIV_FUNCT_STR   "011010"
	#define INST_DIVU_FUNCT_STR  "011011"
	#define INST_AND_FUNCT_STR   "100100"
	#define INST_OR_FUNCT_STR    "100101"
	#define INST_XOR_FUNCT_STR   "100110"
	#define INST_NOR_FUNCT_STR   "100111"
	#define INST_SLT_FUNCT_STR   "101010"
	#define INST_SLL_FUNCT_STR   "000000"
	#define INST_SRL_FUNCT_STR   "000010"
	#define INST_JR_FUNCT_STR    "001000"
	/**@}*/

	/**
	 * @brief Instruction information.
	 */
	struct inst
	{
		const char *name;                     /**< Instruction Name          */
		const char *opcode;                   /**< Instruction Operaion Code */
		const char *funct;                    /**< Instruction Function Code */
		uint32_t (*encode)(const char *); 	  /**< Encoding Function.        */
	};

#endif /* MIPS32_INST_H_ */
