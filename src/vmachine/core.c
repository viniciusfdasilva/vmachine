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

#include <vmachine/cache.h>
uint32_t pc;

/**
 * @brief Fetches an instruction.
 */
uint32_t do_fetch(void)
{
	uint32_t instruction;

	instruction = icache_read(pc);
	pc += 4;
	
	return (instruction);
}

/**
 * Decodes the instruction and sends it to the corresponding execution.
 */
void do_decode(uint32_t instruction)
{
	int opcode 	= instruction & 0xfc000000;
	
	opcode	= opcode >> 24;
	
	char ints_type = instruction_type(opcode);
	
	switch (inst_type)
	{
		case 'R':
			do_execute_R(instruction);			
		break;
		case 'I':
			do_execute_I(instruction);
		break;
		case 'J':
			do_execute_J(instruction);
		break;
	}
}

/**
 * @brief Executes an R instruction.
 */
void do_execute_R(uint32_t instruction)
{
	int opcode 	= instruction & 0xfc000000;
	int rs		= instruction & 0x03e00000;
	int rt		= instruction & 0x001f0000;
	int rd		= instruction & 0x0000f800;
	int shamt	= instruction & 0x000007c0;
	int funct	= instruction & 0x0000002f;

	opcode	= opcode >> 24;
	rs	= rs >> 20;
	rt	= rt >> 16;
	rd	= rd >> 8;
	shamt	= shamt >> 4;
	
	/* TO FINISH */
}

/**
 * @brief Executes an I instruction.
 */
void do_execute_I(uint32_t instruction)
{
	int opcode 	= instruction & 0xfc000000;
	int rs		= instruction & 0x03e00000;
	int rt		= instruction & 0x001f0000;
	int immediate	= instruction & 0x0000ffff;

	opcode	= opcode >> 24;
	
	/* TO FINISH */
}

/**
 * @brief Executes an J instruction.
 */
void do_execute_J(uint32_t instruction)
{
	int opcode 	= instruction & 0xfc000000;
	int address	= instruction & 0x03ffffff;
	
	opcode	= opcode >> 24;
	
	/* TO FINISH */
}

/**
 * @brief Handles Interrupts
 */
void do_interrupts(void)
{
	/* TODO */
}

/**
 * The core_init() initializes a core.
 */
void core_init(void)
{
	cache_init();
}

/**
 * The core_run() function runs a core.
 */
void core_run(void)
{
	while (1)
	{
		do_fetch();
		do_execute();

		do_interrupts();
	}
}


/**
 * Defines the instruction's type.
 */
char instruction_type(int opcode)
{
	switch (opcode)
	{
		case 0:
			return('R');
		case 2:
		case 3:
			return('J');
		default:
			return('I');
	}
}


