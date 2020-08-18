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

R_instruction* r_inst;

/**
 * Select type of instruction extract each word of instruction 
 * and redirects for each function corresponding
 * @param inst[] MIPS instruction of 32 bits
 * */
void select(char inst[])
{
		
	char* opcode = substring(inst,0,5);

	if(strcmp(opcode,"000000") == 0){
		r_init();

		r_inst->opcode = opcode;
		r_inst->rs = substring(inst,6,10);
		r_inst->rt = substring(inst,11,15);
		r_inst->rd = substring(inst,16,20);
		r_inst->shamt = substring(inst,21,25);
		r_inst->funct = substring(inst,26,31);
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
