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

/* Ours */
#include <vmachine.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include<utils.h>

#define SYNTATIC_ERROR "Syntactic error"

// Opcodes of R type
#define R_OPCODE "000000"

// Functions of R type
#define R_ADD "100000"
#define R_ADDU "100001"
#define R_SUB "100010"
#define R_SUBU "100011"
#define R_DIV  "011010"
#define R_DIVU "011011"
#define R_MULT "011000"
#define R_MULTU "011001"
#define R_JR "001000"
#define R_AND "100100"
#define R_NOR "100111"
#define R_OR "100101"
#define R_SLT "101010"
#define R_SLTU "101001"
#define R_SLL "000000"
#define R_SRL "000010"
#define R_SRA "000011"

#define SYNTATIC_ERROR "Syntactic error"

#define index(x) binToDec(x)

// MIPS32 registers
unsigned char* mips_register[] = 
{ 
		{"000000"}, // ("$zero" | "$0")
		{"000001"}, // ("$at" | "$1")
		{"000010"}, // ("$v0" | "$2")
		{"000011"}, // ("$v1" | "$3")
		{"000100"}, // ("$a0" | "$4")
		{"000101"}, // ("$a1" | "$5")
		{"000110"}, // ("$a2" | "$6")
		{"000111"}, // ("$a3" | "$7")
		{"001000"}, // ("$t0" | "$8")
		{"001001"}, // ("$t1" | "$9")
		{"001010"}, // ("$t2" | "$10")
		{"001011"}, // ("$t3" | "$11")
		{"001100"}, // ("$t4" | "$12")
		{"001101"}, // ("$t5" | "$13")
		{"001110"}, // ("$t6" | "$14")
		{"001111"}, // ("$t7" | "$15")
		{"010000"}, // ("$s0" | "$16")
		{"010001"}, // ("$s1" | "$17")
		{"010010"}, // ("$s2" | "$18")
		{"010011"}, // ("$s3" | "$19")
		{"010100"}, // ("$s4" | "$20")
		{"010101"}, // ("$s5" | "$21")
		{"010110"}, // ("$s6" | "$22")
		{"010111"}, // ("$s7" | "$23")
		{"011000"}, // ("$t8" | "$24")
		{"011001"}, // ("$t9" | "$25")
		{"011010"}, // ("$k0" | "$26")
		{"011011"}, // ("$k1" | "$27")
		{"011100"}, // ("$gp" | "$28")
		{"011101"}, // ("$sp" | "$29")
		{"011110"}, // ("$fp" | "$30")
		{"011111"}, // ("$ra" | "$31")
};

/*
	Mips instruction of R type
*/
typedef struct R_instruction
{
	char* opcode;
	char* rs;
	char* rt;
	char* rd;
	char* shamt;
	char* funct;
}R_instruction;

/*
* Start r_inst for let ready to use
*/
void r_init()
{
	r_inst = (R_instruction*)malloc(sizeof(R_instruction));
	r_inst->opcode = "";
	r_inst->rs = "";
	r_inst->rd = "";
	r_inst->rt = "";
	r_inst->shamt = "";
	r_inst->funct = "";
}

R_instruction* r_inst;

/**
 * Check if these two parameters are equals.
 * @param tk1
 * @param tk2
 * */
static void match(char* tk1,char* tk2)
{
	if(!equals(tk1,tk2)) printf("%s",SYNTATIC_ERROR);
}

/*
* r_procedure_Function()
*/
static void r_procedure_Function()
{

}

/*
* r_procefure_Format()
*/
static void r_procedure_Format()
{

}

/*
 * First rule of grammar and Parsing tree
*/
static void r_procedure_S()
{
	if(equals(R_OPCODE,r_inst->opcode))
	{
		match(R_OPCODE,r_inst->opcode);
	}
	r_procedure_Format();
	r_pocedure_functionOpcode();
}

/**
 * Translate binary code MIPS32 in RV32.
 * Opening process of translate
 */
static void r_translator()
{
	r_procedure_S(r_inst);
}

/**
 * Select type of instruction.
 * Extract each word of instruction 
 * and redirects for each function corresponding
 * @param inst[] MIPS instruction of 32 bits
 * */
void select(char inst[])
{
		
	char* opcode = substring(inst,0,5);

	if(equals(opcode,R_OPCODE)){
		r_init();

		r_inst->opcode = opcode;
		r_inst->rs = substring(inst,6,10);
		r_inst->rt = substring(inst,11,15);
		r_inst->rd = substring(inst,16,20);
		r_inst->shamt = substring(inst,21,25);
		r_inst->funct = substring(inst,26,31);
		r_translator();
	}
}

/**
 * The engine_run() function translates a binary code into another.
 */
word_t engine_run(uint32_t instruction)
{
	char string_instruction[32];
	itoa(instruction,string_instruction,10);
	select(string_instruction);

	return (instruction);
}
