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

#include <vmachine/core.h>
#include <vmachine/isa.h>
#include <arch.h>

using namespace vmachine;

// Executes a R-Type instruction.
void Core::executeR(isa32::word_t inst)
{
	isa32::word_t rs	 = ((inst >> INST_SHIFT_RS) & INST_MASK_RS);
	isa32::word_t rt	 = ((inst >> INST_SHIFT_RT) & INST_MASK_RT);
	isa32::word_t rd     = ((inst >> INST_SHIFT_RD) & INST_MASK_RD);
	isa32::word_t shamt  = ((inst >> INST_SHIFT_SHAMT) & INST_MASK_SHAMT);
	isa32::word_t funct  = ((inst >> INST_SHIFT_FUNCT) & INST_MASK_FUNCT);

	// Parse function.
	switch(funct)
	{
		case INST_FUNCT_ADD:
			regs[rd] = regs[rs] + regs[rt];
			break;

		case INST_FUNCT_ADDU:
			regs[rd] = regs[rs] + regs[rt];
			break;

		case INST_FUNCT_AND:
			regs[rd] = regs[rs] & regs[rt];
			break;

		case INST_FUNCT_NOR:
			regs[rd] = ~(regs[rs] | regs[rt]);
			break;

		case INST_FUNCT_OR:
			regs[rd] = regs[rs] | regs[rt];
			break;

		case INST_FUNCT_SLT:
			regs[rd] = (regs[rs] < regs[rt]) ? 1 : 0;
			break;

		case INST_FUNCT_SLTU:
			regs[rd] = (regs[rs] < regs[rt]) ? 1 : 0;
			break;

		case INST_FUNCT_SUB:
			regs[rd] = regs[rs] - regs[rt];
			break;

		case INST_FUNCT_SUBU:
			regs[rd] = regs[rs] - regs[rt];
			break;

		case INST_FUNCT_XOR:
			regs[rd] = regs[rs] ^ regs[rt];
			break;

		case INST_FUNCT_JR:
			pc = regs[rs];
			break;

		case INST_FUNCT_SLL:
			regs[rd] = regs[rt] << shamt;
			break;

		case INST_FUNCT_SRL:
			regs[rd] = regs[rt] >> shamt;
			break;

		case INST_FUNCT_DIV:
			lo = regs[rs]/regs[rt];
			hi = regs[rs] % regs[rt];
			break;

		case INST_FUNCT_DIVU:
			lo = regs[rs]/regs[rt];
			hi = regs[rs] % regs[rt];
			break;
		case INST_FUNCT_MFHI:
			regs[rd] = hi;
			break;

		case INST_FUNCT_MFLO:
			regs[rd] = lo;
			break;

		case INST_FUNCT_MULT:
			lo = regs[rs] * regs[rt];
			break;

		case INST_FUNCT_MULTU:
			lo = regs[rs] * regs[rt];
			break;

		case INST_FUNCT_SRA:
			regs[rd] = regs[rt] >> shamt;
			break;

		// Unkonwn instruction.
		default:
			break;
	}

	if (funct != INST_FUNCT_JR)
		pc += sizeof(isa32::word_t);
}

// Executes a I-Type instruction.
void Core::executeI(isa32::word_t inst)
{
	isa32::word_t opcode = ((inst >> INST_SHIFT_OPCODE) & INST_MASK_OPCODE);
	isa32::word_t rs	 = ((inst >> INST_SHIFT_RS) & INST_MASK_RS);
	isa32::word_t rt	 = ((inst >> INST_SHIFT_RT) & INST_MASK_RT);
	isa32::word_t imm    = ((inst >> INST_SHIFT_IMM) & INST_MASK_IMM);

	switch(opcode)
	{
		case INST_OPCODE_ADDI:
			regs[rt] = regs[rs] + imm;
			break;

		case INST_OPCODE_ADDIU:
			regs[rt] = regs[rs] + imm;
			break;

		case INST_OPCODE_ANDI:
			regs[rt] = regs[rs] & imm;
			break;

		case INST_OPCODE_BEQ:
			pc += (regs[rs] == regs[rt]) ? (imm << 2) : 4;
			break;

		case INST_OPCODE_BNE:
			pc += (regs[rs] != regs[rt]) ? (imm << 2) : 4;
			break;

		case INST_OPCODE_LBU:
			regs[rt] = memory_.read(regs[rs] + imm);
			break;

		case INST_OPCODE_LHU:
			regs[rt] = memory_.read(regs[rs] + imm);
			break;

		case INST_OPCODE_LL:
			regs[rt] = memory_.read(regs[rs] + imm);
			break;

		case INST_OPCODE_LUI:
			regs[rt] = imm << 16;
			break;

		case INST_OPCODE_LW:
			regs[rt] = memory_.read(regs[rs] + imm);
			break;

		case INST_OPCODE_ORI:
			regs[rt] = regs[rs] | imm; 
			break;

		case INST_OPCODE_SLTI:
			regs[rt] = (regs[rs] < imm) ? 1 : 0;
			break;

		case INST_OPCODE_SLTIU:
			regs[rt] = (regs[rs] < imm) ? 1 : 0;
			break;

		case INST_OPCODE_SB:
			memory_.write((regs[rs] + imm), (0xff & regs[rt]));
			break;

		case INST_OPCODE_SH:
			memory_.write((regs[rs] + imm), regs[rt]);
			break;

		case INST_OPCODE_SW:
			memory_.write((regs[rs] + imm), regs[rt]);
			break;

		case INST_OPCODE_XORI:
			regs[rt] = regs[rs] ^ imm;
			break;

		// Unkonwn instruction.
		default:
			break;
	}

	if (opcode != INST_OPCODE_BEQ && opcode != INST_OPCODE_BNE)
		pc += sizeof(isa32::word_t);
}

// Executes a J-Type instruction.
void Core::executeJ(isa32::word_t inst)
{
	isa32::word_t opcode  = ((inst >> INST_SHIFT_OPCODE) & INST_MASK_OPCODE);
	isa32::word_t address = ((inst >> INST_SHIFT_TARGET) & INST_MASK_TARGET);

	switch(opcode)
	{
		case INST_OPCODE_J:
			pc |= (address << 2);
			break;

		case INST_OPCODE_JAL:
			regs[0x1f] = pc + 8;
			pc |= (address << 2);
			break;

		// Unkonwn instruction.
		default:
			break;
	}
}

// Decodes an instruction.
Core::execute_fn Core::decode(isa32::word_t inst)
{
	execute_fn fn;
	isa32::word_t opcode;

	opcode = (inst >> INST_SHIFT_OPCODE) & INST_MASK_OPCODE;

	switch(opcode)
	{
		// R-Type Instruction
		case 0:
			fn = &Core::executeR;
			break;

		// J-Type Instruction
		case 2:
		case 3:
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