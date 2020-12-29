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

// Ours
#include <vmachine/cache.h>
#include <vmachine/core.h>
#include <vmachine/isa.h>
#include <vmachine/memory.h>
#include <arch.h>
#include <config.h>
#include <utils.h>

using namespace vmachine;

// Executes a R-Type instruction.
void Core::executeR(isa32::word_t inst)
{
	isa32::word_t funct_7 = ((inst >> INST_SHIFT_FUNCT_7) & INST_MASK_FUNCT_7);
	isa32::word_t rs1     = ((inst >> INST_SHIFT_RS_1)    & INST_MASK_RS_1);
	isa32::word_t rs2     = ((inst >> INST_SHIFT_RS_2)    & INST_MASK_RS_2);
	isa32::word_t funct_3 = ((inst >> INST_SHIFT_FUNCT_3) & INST_MASK_FUNCT_3);
	isa32::word_t rd      = ((inst >> INST_SHIFT_RD)      & INST_MASK_RD);

	// Parse function.
	switch(funct_3)
	{
		case INST_ADD_SUB_FUNCT_3:
			if (funct_7 == INST_ADD_FUNCT_7)
				registers[rd] = registers[rs1] + registers[rs1];
			else if (funct_7 == INST_SUB_FUNCT_7)
				registers[rd] = registers[rs1] - registers[rs2];
		break;
		case INST_SLL_FUNCT_3:
			registers[rd] = registers[rs1] << registers[rs2];
		break;
		case INST_SLT_FUNCT_3:
			registers[rd] = (registers[rs1] < registers[rs2]) ? 1 : 0;
		break;
		case INST_SLTU_FUNCT_3:
			registers[rd] = (registers[rs1] < registers[rs2]) ? 1 : 0;
		break;
		case INST_XOR_FUNCT_3:
			registers[rd] = registers[rs1] ^ registers[rs2];
		break;
		case INST_SRL_SRA_FUNCT_3:
			registers[rd] = registers[rs1] >> registers[rs2];
		break;
		case INST_OR_FUNCT_3:
			registers[rd] = registers[rs1] | registers[rs2];
		break;
		case INST_AND_FUNCT_3:
			registers[rd] = registers[rs1] & registers[rs2];
		break;
		default:
			error("Unknown instruction");
		break;
	}
	pc += sizeof(isa32::word_t);
}

// Executes a I-Type instruction.
void Core::executeI(isa32::word_t inst)
{
	isa32::word_t immediate_1 = ((inst >> INST_SHIFT_IMMEDIATE_I_TYPE) & INST_MASK_IMMEDIATE_I_TYPE);
	isa32::word_t rs1         = ((inst >> INST_SHIFT_RS_1)             & INST_MASK_RS_1);
	isa32::word_t funct_3     = ((inst >> INST_SHIFT_FUNCT_3)          & INST_MASK_FUNCT_3);
	isa32::word_t rd          = ((inst >> INST_SHIFT_RD)               & INST_MASK_RD);
	isa32::word_t shamt       = ((inst >> INST_SHIFT_RS_2)             & INST_MASK_RS_2);
	isa32::word_t opcode      = inst                                   & INST_MASK_OPCODE;

	Cache cache(VMACHINE_DEFAULT_CACHE_SIZE);

	switch(opcode)
	{
		case I_TYPE_JUMPER_INSTRUCTION:
			if (funct_3 == INST_JALR_FUNCT_3)
			{
				registers[rd] = pc + 4;
				pc += ((registers[rs1] + immediate_1) & (~0u ^ 3u));
			}
		break;
		case I_TYPE_LOAD_INSTRUCTIONS:
			if (funct_3 == INST_LB_FUNCT_3)
				registers[rd] = cache.read(registers[rs1] + immediate_1);
			else if (funct_3 == INST_LH_FUNCT_3)
				registers[rd] = cache.read(registers[rs1] + immediate_1);
			else if (funct_3 == INST_LW_FUNCT_3)
				registers[rd] = cache.read(registers[rs1] + immediate_1);
			else if (funct_3 == INST_LBU_FUNCT_3)
				registers[rd] = cache.read(registers[rs1] + immediate_1);
			else if (funct_3 == INST_LHU_FUNCT_3)
				registers[rd] = cache.read(registers[rs1] + immediate_1);
		break;
		case I_TYPE_REGISTERS_INSTRUCTIONS:
			if (funct_3 == INST_ADDI_FUNCT_3)
				registers[rd] = registers[rs1] + immediate_1;
			else if (funct_3 == INST_SLTI_FUNCT_3)
				registers[rd] = (registers[rs1] < immediate_1) ? 1 : 0;
			else if (funct_3 == INST_SLTIU_FUNCT_3)
				registers[rd] = (registers[rs1] < immediate_1) ? 1 : 0;
			else if (funct_3 == INST_XORI_FUNCT_3)
				registers[rd] = registers[rs1] ^ immediate_1;
			else if (funct_3 == INST_ORI_FUNCT_3)
				registers[rd] = registers[rs1] | immediate_1;
			else if (funct_3 == INST_ANDI_FUNCT_3)
				registers[rd] = registers[rs1] & immediate_1;
			else if (funct_3 == INST_SLLI_FUNCT_3)
				registers[rd] = registers[rs1] << shamt;
			else if (funct_3 == INST_SRLI_FUNCT_3)
				registers[rd] = registers[rs1] >> shamt;
			else if (funct_3 == INST_SRAI_FUNCT_3)
				registers[rd] = registers[rs1] >> shamt;
		break;
		case I_TYPE_FENCE_INSTRUCTIONS:
		case I_TYPE_CALL_BREAKPOINT_CRS_INSTRUCTIONS:
			//if (funct_3 == INST_ECALL_FUNCT_3) {}
			//if (funct_3 == INST_EBREAK_FUNCT_3) {}
			//if (funct_3 == INST_CSRRW_FUNCT_3) {}
			//if (funct_3 == INST_CSRRS_FUNCT_3) {}
			//if (funct_3 == INST_CSRRC_FUNCT_3) {}
			//if (funct_3 == INST_CSRRWI_FUNCT_3) {}
			//if (funct_3 == INST_CSRRSI_FUNCT_3) {}
			//if (funct_3 == INST_CSRRCI_FUNCT_3) {}
		default:
			error("Unknown instruction");
		break;
	}

	if (opcode != I_TYPE_JUMPER_INSTRUCTION)
		pc += sizeof(isa32::word_t);
}

// Executes a J-Type instruction.
void Core::executeJ(isa32::word_t inst)
{
	isa32::word_t rd      = ((inst >> INST_SHIFT_RD)        & INST_MASK_RD);
	isa32::word_t address = ((inst >> INST_SHIFT_IMMEDIATE) & INST_MASK_IMMEDIATE);
	isa32::word_t opcode  = inst                            & INST_MASK_OPCODE;

	switch(opcode)
	{
		case INST_OPCODE_JAL:
			registers[rd] = pc + sizeof(isa32::word_t);
			pc += address;
		break;
		default:
			error("Unknown instruction");
		break;
	}
}

// Executes a S-Type instruction.
void Core::executeS(isa32::word_t inst)
{
	isa32::word_t immediate_1 = ((inst >> INST_SHIFT_FUNCT_7) & INST_MASK_FUNCT_7);
	isa32::word_t rs2         = ((inst >> INST_SHIFT_RS_2)    & INST_MASK_RS_2);
	isa32::word_t rs1         = ((inst >> INST_SHIFT_RS_1)    & INST_MASK_RS_1);
	isa32::word_t funct_3     = ((inst >> INST_SHIFT_FUNCT_3) & INST_MASK_FUNCT_3);

	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	switch (funct_3)
	{
		case INST_SB_FUNCT_3:
			memory.write(registers[rs1] + immediate_1, registers[rs2]);
		break;
		case INST_SH_FUNCT_3:
			memory.write(registers[rs1] + immediate_1, registers[rs2]);
		break;
		case INST_SW_FUNCT_3:
			memory.write(registers[rs1] + immediate_1, registers[rs2]);
		break;
		default:
			error("Unknown instruction");
		break;
	}
	pc += sizeof(isa32::word_t);
}

// Executes a B-Type instruction.
void Core::executeB(isa32::word_t inst)
{
	isa32::word_t immediate_1 = ((inst >> INST_SHIFT_FUNCT_7) & INST_MASK_FUNCT_7);
	isa32::word_t rs2         = ((inst >> INST_SHIFT_RS_2)    & INST_MASK_RS_2);
	isa32::word_t rs1         = ((inst >> INST_SHIFT_RS_1)    & INST_MASK_RS_1);
	isa32::word_t funct_3     = ((inst >> INST_SHIFT_FUNCT_3) & INST_MASK_FUNCT_3);

	switch (funct_3)
	{
		case INST_BEQ_FUNCT_3:
			if (registers[rs1] == registers[rs2])
				pc += immediate_1;
		break;
		case INST_BNE_FUNCT_3:
			if (registers[rs1] != registers[rs2])
				pc += immediate_1;
		break;
		case INST_BLT_FUNCT_3:
			if (registers[rs1] < registers[rs2])
				pc += immediate_1;
		break;
		case INST_BGE_FUNCT_3:
			if (registers[rs1] >= registers[rs2])
				pc += immediate_1;
		break;
		case INST_BLTU_FUNCT_3:
			if (registers[rs1] < registers[rs2])
				pc += immediate_1;
		break;
		case INST_BGEU_FUNCT_3:
			if (registers[rs1] >= registers[rs2])
				pc += immediate_1;
		break;
		default:
			error("Unknown instruction");
		break;
	}
}

// Executes a U-Type instruction.
void Core::executeU(isa32::word_t inst)
{
	isa32::word_t immediate = ((inst >> INST_SHIFT_IMMEDIATE) & INST_MASK_IMMEDIATE);
	isa32::word_t rd        = ((inst >> INST_SHIFT_RD)        & INST_MASK_RD);
	isa32::word_t opcode    = inst                            & INST_MASK_OPCODE;

	switch(opcode)
	{
		case INST_OPCODE_LUI:
			registers[rd] = immediate << 12;
		break;
		case INST_OPCODE_AUIPC:
			registers[rd] = pc + (immediate << 12);
		break;
		default:
			error("Unknown instruction");
		break;
	}

	pc += sizeof(isa32::word_t);
}

// Decodes an instruction.
Core::execute_fn Core::decode(isa32::word_t inst)
{
	execute_fn fn;
	isa32::word_t opcode;

	opcode = inst & INST_MASK_OPCODE;

	switch(opcode)
	{
		// U-Type Instruction
		case U_TYPE_IMMEDIATE_INSTRUCTION:
		case U_TYPE_PC_INSTRUCTION:
			fn = &Core::executeU;
		break;

		// B-Type Instruction
		case B_TYPE_INSTRUCTIONS:
			fn = &Core::executeB;
		break;

		// B-Type Instruction
		case S_TYPE_INSTRUCTIONS:
			fn = &Core::executeS;
		break;

		// R-Type Instruction
		case R_TYPE_INSTRUCTIONS:
			fn = &Core::executeR;
		break;

		// J-Type Instruction
		case J_TYPE_INSTRUCTION:
			fn = &Core::executeJ;
		break;

		// I-Type Instruction
		default:
			fn = &Core::executeI;
		break;
	}

	return (fn);
}

// Executes an instruction.
void Core::execute(isa32::word_t inst)
{
	auto execute = decode(inst);

	(this->*execute)(inst);
}

// Fetches an instruction.
isa32::word_t Core::fetch(void)
{
	isa32::word_t inst;

	inst = memory_.read(pc);

	return (inst);
}

// Runs the target core.
void Core::run(void)
{
	while (true)
	{
		isa32::word_t inst;

		inst = fetch();

		execute(inst);

		pc += sizeof(isa32::word_t);
	}
}
