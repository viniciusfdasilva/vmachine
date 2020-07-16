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
#include <arch/mips32.h>
#include <utils.h>

#define VMACHINE_INSTRUCTION_OPCODE 0xfc000000
#define VMACHINE_INSTRUCTION_RS 0x03e00000
#define VMACHINE_INSTRUCTION_RT 0x001f0000
#define VMACHINE_INSTRUCTION_RD 0x0000f800
#define VMACHINE_INSTRUCTION_SHAMT 0x000007c0
#define VMACHINE_INSTRUCTION_FUNCT 0x0000002f
#define VMACHINE_INSTRUCTION_IMMEDIATE 0x0000ffff
#define VMACHINE_INSTRUCTION_ADDRESS 0x03ffffff

#define VMACHINE_INSTRUCTION_SHIFT_OPCODE 24
#define VMACHINE_INSTRUCTION_SHIFT_RS 20
#define VMACHINE_INSTRUCTION_SHIFT_RT 16
#define VMACHINE_INSTRUCTION_SHIFT_RD 8
#define VMACHINE_INSTRUCTION_SHIFT_SHAMT 4

#define NUMBER_OF_REGISTERS 32

uint32_t pc = 0;
uint32_t registers[NUMBER_OF_REGISTERS];
uint32_t hi;
uint32_t lo;

/**
 * Advances PC value
 */
void advances_pc(uint32_t offset) {
	pc += offset;
}

/**
 * @brief Fetches an instruction.
 */
uint32_t do_fetch(void)
{
	uint32_t instruction;

	instruction = icache_read(pc);
	advances_pc(4);

	return (instruction);
}

/**
 * Defines the instruction's type.
 */
char instruction_type(uint32_t opcode)
{
        switch (opcode)
        {
                case 0:
                        return('R');
		break;
                case 2:
                case 3:
                        return('J');
		break;
                default:
                        return('I');
        }
}

/**
 * @brief Executes an R instruction.
 */
void do_execute_R(uint32_t instruction)
{
	uint32_t opcode = instruction & VMACHINE_INSTRUCTION_OPCODE;
	uint32_t rs     = instruction & VMACHINE_INSTRUCTION_RS;
	uint32_t rt     = instruction & VMACHINE_INSTRUCTION_RT;
	uint32_t rd     = instruction & VMACHINE_INSTRUCTION_RD;
	uint32_t shamt  = instruction & VMACHINE_INSTRUCTION_SHAMT;
	uint32_t funct  = instruction & VMACHINE_INSTRUCTION_FUNCT;

	opcode = opcode >> VMACHINE_INSTRUCTION_SHIFT_OPCODE;
	rs     = rs >> VMACHINE_INSTRUCTION_SHIFT_RS;
	rt     = rt >> VMACHINE_INSTRUCTION_SHIFT_RD;
	rd     = rd >> VMACHINE_INSTRUCTION_SHIFT_RD;
	shamt  = shamt >> VMACHINE_INSTRUCTION_SHIFT_SHAMT;

	// Assembling the operations based on funct

	switch(funct)
	{
		case INST_ADD_FUNCT:
			registers[rd] = registers[rs] + registers[rt];
		break;
		case INST_ADDU_FUNCT:
			registers[rd] = registers[rs] + registers[rt];
		break;
		case INST_AND_FUNCT:
			registers[rd] = registers[rs] & registers[rt];
		break;
		case INST_NOR_FUNCT:
			registers[rd] = !(registers[rs] | registers[rt]);
		break;
		case INST_OR_FUNCT:
			registers[rd] = registers[rs] | registers[rt];
		break;
		case INST_SLT_FUNCT:
			registers[rd] = (registers[rs] < registers[rt]) ? 1 : 0;
		break;
		case INST_SLTU_FUNCT:
			registers[rd] = (registers[rs] < registers[rt]) ? 1 : 0;
		break;
		case INST_SUB_FUNCT:
			registers[rd] = registers[rs] - registers[rt];
		break;
		case INST_SUBU_FUNCT:
			registers[rd] = registers[rs] - registers[rt];
		break;
		case INST_XOR_FUNCT:
			registers[rd] = registers[rs] ^ registers[rt];
		break;
		case INST_JR_FUNCT:
                        pc = registers[rs];
                break;
		case INST_SLL_FUNCT:
                        registers[rd] = registers[rt] << shamt;
                break;
		case INST_SRL_FUNCT:
                        registers[rd] = registers[rt] >> shamt;
                break;
		case INST_DIV_FUNCT:
                        lo = registers[rs] / registers[rt];
			hi = registers[rs] % registers[rt];
                break;
		case INST_DIVU_FUNCT:
                        lo = registers[rs] / registers[rt];
			hi = registers[rs] % registers[rt];
                break;
		case INST_MFHI_FUNCT:
                        registers[rd] = hi;
                break;
                case INST_MFLO_FUNCT:
                        registers[rd] = lo;
                break;
                case INST_MULT_FUNCT:
                        lo = registers[rs] * registers[rt];
                break;
                case INST_MULTU_FUNCT:
                        lo = registers[rs] * registers[rt];
                break;
                case INST_SRA_FUNCT:
                        registers[rd] = registers[rt] >> shamt;
                break;
		default:
			error("unknown instruction");
                break;
	}

	if (funct != INST_JR_FUNCT) {
		advances_pc(4);
	}
}

/**
 * @brief Executes an I instruction.
 */
void do_execute_I(uint32_t instruction)
{
	uint32_t opcode = instruction & VMACHINE_INSTRUCTION_OPCODE;
	uint32_t rs	    = instruction & VMACHINE_INSTRUCTION_RS;
	uint32_t rt	    = instruction & VMACHINE_INSTRUCTION_RT;
	uint32_t imm    = instruction & VMACHINE_INSTRUCTION_IMMEDIATE;

	opcode = opcode >> VMACHINE_INSTRUCTION_SHIFT_OPCODE;

	/* TO FINISH */
	((void) rs);
	((void) rt);
	((void) imm);
}

/**
 * @brief Executes an J instruction.
 */
void do_execute_J(uint32_t instruction)
{
	uint32_t opcode  = instruction & VMACHINE_INSTRUCTION_OPCODE;
	uint32_t address = instruction & VMACHINE_INSTRUCTION_ADDRESS;

	opcode = opcode >> VMACHINE_INSTRUCTION_SHIFT_OPCODE;

	/* TO FINISH */
	((void) address);
}

/**
 * Decodes the instruction and sends it to the corresponding execution.
 */
void do_decode(uint32_t instruction)
{
        uint32_t opcode = instruction & VMACHINE_INSTRUCTION_OPCODE;

        opcode  = opcode >> VMACHINE_INSTRUCTION_SHIFT_OPCODE;

        char inst_type = instruction_type(opcode);

        switch (inst_type)
        {
                case 'R':
                        do_execute_R(instruction);
		break;
                case 'I':
                        do_execute_I(instruction);
		break;
                default:
                        do_execute_J(instruction);
        }
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
		uint32_t instr;

		instr = do_fetch();

		do_decode(instr);

		do_interrupts();
	}
}
