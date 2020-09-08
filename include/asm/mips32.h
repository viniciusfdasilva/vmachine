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


#ifndef ASM_MIPS32_H_
#define ASM_MIPS32_H_

	#include <asm/inst.h>
	#include <asm/regs.h>
	#include <stdlib.h>

	/**
	 * @brief Struct renames with typedef
	 */
	typedef struct reg reg;
	typedef struct inst inst;

	/**
	 * @brief Opcodes of R type
	 */
	#define R_OPCODE "000000"

	/**
	 * @name Name of Registers
	 */
	/**@{*/
	#define REG_ZERO_NAME "zero"
	#define REG_AT_NAME   "at"
	#define REG_V0_NAME   "v0"
	#define REG_V1_NAME   "v1"
	#define REG_A0_NAME   "a0"
	#define REG_A1_NAME   "a1"
	#define REG_A2_NAME   "a2"
	#define REG_A3_NAME   "a3"
	#define REG_T0_NAME   "t0"
	#define REG_T1_NAME   "t1"
	#define REG_T2_NAME   "t2"
	#define REG_T3_NAME   "t3"
	#define REG_T4_NAME   "t4"
	#define REG_T5_NAME   "t5"
	#define REG_T6_NAME   "t6"
	#define REG_T7_NAME   "t7"
	#define REG_S0_NAME   "s0"
	#define REG_S1_NAME   "s1"
	#define REG_S2_NAME   "s2"
	#define REG_S3_NAME   "s3"
	#define REG_S4_NAME   "s4"
	#define REG_S5_NAME   "s5"
	#define REG_S6_NAME   "s6"
	#define REG_S7_NAME   "s7"
	#define REG_T8_NAME   "t8"
	#define REG_T9_NAME   "t9"
	#define REG_K0_NAME   "k0"
	#define REG_K1_NAME   "k1"
	#define REG_GP_NAME   "gp"
	#define REG_SP_NAME   "sp"
	#define REG_FP_NAME   "fp"
	#define REG_RA_NAME   "ra"
	/**@}*/

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

	typedef struct R_instruction
	{
		inst* instruction;
		reg* sa;
		reg* rs;
		reg* rd;
		reg* rt;
	}R_instruction;

	R_instruction* init(){
		R_instruction* r_instruction = (R_instruction*)malloc(sizeof(R_instruction));
		
	//	r_instruction->instruction->encode = "";
		r_instruction->instruction->funct = "";
		r_instruction->instruction->name = "";
		r_instruction->instruction->opcode = "";
		
		r_instruction->sa->code = "";
		r_instruction->sa->name = "";

		r_instruction->rd->code = "";
		r_instruction->rd->name = "";

		r_instruction->rt->code = "";
		r_instruction->rt->name = "";

		r_instruction->rs->code = "";
		r_instruction->rs->name = "";
		
		return r_instruction;
	}

	void finish(R_instruction* instruction)
	{ 
		free(instruction);
	}
#endif /* ASM_MIPS32_H_ */
