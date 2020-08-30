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

// Theirs
#include <cstdlib>
#include <iostream>
#include <unordered_map>

// Ours
#include <asm/mips32.h>
#include <arch/mips32.h>

using namespace mips32;

/**
 * @brief Instruction information.
 */
class Instruction
{
	public:

		isa32::word_t opcode;
		isa32::word_t funct;
		isa32::word_t(*encode)(const std::vector<const char *> &tokens);
};

// Forward definitions.
static isa32::word_t encode_instruction_R_generic(const std::vector<const char *> &inst);
static isa32::word_t encode_instruction_R_shift(const std::vector<const char *> &tokens);
static isa32::word_t encode_instruction_R_muldiv(const std::vector<const char *> &tokens);
static isa32::word_t encode_instruction_R_jr(const std::vector<const char *> &tokens);
static isa32::word_t encode_instruction_I_generic(const std::vector<const char *> &inst);
static isa32::word_t encode_instruction_I_ls(const std::vector<const char *> &inst);
static isa32::word_t encode_instruction_J_generic(const std::vector<const char *> &inst);

//==============================================================================
// Lookup Tables
//==============================================================================

// Map of Registers
static std::unordered_map<std::string, uint32_t> registers = {
	{ REG_NAME_ZERO , REG_ZERO,  },
	{ REG_NAME_AT,    REG_AT,    },
	{ REG_NAME_V0,    REG_V0,    },
	{ REG_NAME_V1,    REG_V1,    },
	{ REG_NAME_A0,    REG_A0,    },
	{ REG_NAME_A1,    REG_A1,    },
	{ REG_NAME_A2,    REG_A2,    },
	{ REG_NAME_A3,    REG_A3,    },
	{ REG_NAME_T0,    REG_T0,    },
	{ REG_NAME_T1,    REG_T1,    },
	{ REG_NAME_T2,    REG_T2,    },
	{ REG_NAME_T3,    REG_T3,    },
	{ REG_NAME_T4,    REG_T4,    },
	{ REG_NAME_T5,    REG_T5,    },
	{ REG_NAME_T6,    REG_T6,    },
	{ REG_NAME_T7,    REG_T7,    },
	{ REG_NAME_S0,    REG_S0,    },
	{ REG_NAME_S1,    REG_S1,    },
	{ REG_NAME_S2,    REG_S2,    },
	{ REG_NAME_S3,    REG_S3,    },
	{ REG_NAME_S4,    REG_S4,    },
	{ REG_NAME_S5,    REG_S5,    },
	{ REG_NAME_S6,    REG_S6,    },
	{ REG_NAME_S7,    REG_S7,    },
	{ REG_NAME_T8,    REG_T8,    },
	{ REG_NAME_T9,    REG_T9,    },
	{ REG_NAME_K0,    REG_K0,    },
	{ REG_NAME_K1,    REG_K1,    },
	{ REG_NAME_GP,    REG_GP,    },
	{ REG_NAME_SP,    REG_SP,    },
	{ REG_NAME_FP,    REG_FP,    },
	{ REG_NAME_RA,    REG_RA,    },
};

// Map of Instructions
static std::unordered_map<std::string, Instruction> instructions = {
	{ INST_NAME_ADD,  { INST_OPCODE_ADD,  INST_FUNCT_ADD,  encode_instruction_R_generic } },
	{ INST_NAME_ADDI, { INST_OPCODE_ADDI, INST_FUNCT_NONE, encode_instruction_I_generic } },
	{ INST_NAME_SUB,  { INST_OPCODE_SUB,  INST_FUNCT_SUB,  encode_instruction_R_generic } },
	{ INST_NAME_MULT, { INST_OPCODE_MULT, INST_FUNCT_MULT, encode_instruction_R_muldiv  } },
	{ INST_NAME_DIV,  { INST_OPCODE_DIV,  INST_FUNCT_DIV,  encode_instruction_R_muldiv  } },
	{ INST_NAME_AND,  { INST_OPCODE_AND,  INST_FUNCT_AND,  encode_instruction_R_generic } },
	{ INST_NAME_ANDI, { INST_OPCODE_ANDI, INST_FUNCT_NONE, encode_instruction_I_generic } },
	{ INST_NAME_OR,   { INST_OPCODE_OR,   INST_FUNCT_OR,   encode_instruction_R_generic } },
	{ INST_NAME_ORI,  { INST_OPCODE_ORI,  INST_FUNCT_NONE, encode_instruction_I_generic } },
	{ INST_NAME_XOR,  { INST_OPCODE_XOR,  INST_FUNCT_XOR,  encode_instruction_R_generic } },
	{ INST_NAME_XOR,  { INST_OPCODE_NOR,  INST_FUNCT_NOR,  encode_instruction_R_generic } },
	{ INST_NAME_SLT,  { INST_OPCODE_SLT,  INST_FUNCT_SLT,  encode_instruction_R_generic } },
	{ INST_NAME_SLTI, { INST_OPCODE_SLTI, INST_FUNCT_NONE, encode_instruction_I_generic } },
	{ INST_NAME_SLL,  { INST_OPCODE_SLL,  INST_FUNCT_SLL,  encode_instruction_R_shift   } },
	{ INST_NAME_SRL,  { INST_OPCODE_SRL,  INST_FUNCT_SRL,  encode_instruction_R_shift   } },
	{ INST_NAME_LW,   { INST_OPCODE_LW,   INST_FUNCT_NONE, encode_instruction_I_ls      } },
	{ INST_NAME_SW,   { INST_OPCODE_SW,   INST_FUNCT_NONE, encode_instruction_I_ls      } },
	{ INST_NAME_BEQ,  { INST_OPCODE_BEQ,  INST_FUNCT_NONE, encode_instruction_I_generic } },
	{ INST_NAME_BNE,  { INST_OPCODE_BNE,  INST_FUNCT_NONE, encode_instruction_I_generic } },
	{ INST_NAME_J,    { INST_OPCODE_J,    INST_FUNCT_NONE, encode_instruction_J_generic } },
	{ INST_NAME_JR,   { INST_OPCODE_JR,   INST_FUNCT_JR,   encode_instruction_R_jr      } },
	{ INST_NAME_JAL,  { INST_OPCODE_JAL,  INST_FUNCT_NONE, encode_instruction_J_generic } },
};

//==============================================================================
// Encoding Functions
//==============================================================================

/**
 * @brief Encodes a R-type instruction.
 *
 * @param tokens Instruction tokens.
 *
 * @returns The encoded instruction.
 */
static isa32::word_t encode_instruction_R_generic(const std::vector<const char *> &tokens)
{
	// TODO: sanity check tokens.

	Instruction i = instructions[tokens[0]];
	isa32::word_t opcode = i.opcode;
	isa32::word_t rd = registers[tokens[1]];
	isa32::word_t rs = registers[tokens[2]];
	isa32::word_t rt = registers[tokens[3]];
	isa32::word_t funct = i.funct;

	isa32::word_t inst = 0;
	inst |= (opcode & INST_MASK_OPCODE) << INST_SHIFT_OPCODE;
	inst |= (rs & INST_MASK_RS) << INST_SHIFT_RS;
	inst |= (rt & INST_MASK_RT) << INST_SHIFT_RT;
	inst |= (rd & INST_MASK_RD) << INST_SHIFT_RD;
	inst |= (funct & INST_MASK_FUNCT) << INST_SHIFT_FUNCT;

	return (inst);
}

/**
 * @brief Encodes a shift R-type instruction.
 *
 * @param tokens Instruction tokens.
 *
 * @returns The encoded instruction.
 */
static isa32::word_t encode_instruction_R_shift(const std::vector<const char *> &tokens)
{
	// TODO: sanity check tokens.

	Instruction i = instructions[tokens[0]];
	isa32::word_t opcode = i.opcode;
	isa32::word_t rd = registers[tokens[1]];
	isa32::word_t rt = registers[tokens[2]];
	isa32::word_t shamt = std::stoul(tokens[3]);
	isa32::word_t funct = i.funct;

	isa32::word_t inst = 0;
	inst |= (opcode & INST_MASK_OPCODE) << INST_SHIFT_OPCODE;
	inst |= (rt & INST_MASK_RT) << INST_SHIFT_RT;
	inst |= (rd & INST_MASK_RD) << INST_SHIFT_RD;
	inst |= (shamt & INST_MASK_SHAMT) << INST_SHIFT_SHAMT;
	inst |= (funct & INST_MASK_FUNCT) << INST_SHIFT_FUNCT;

	return (inst);
}

/**
 * @brief Encodes a mult/div R-type instruction.
 *
 * @param tokens Instruction tokens.
 *
 * @returns The encoded instruction.
 */
static isa32::word_t encode_instruction_R_muldiv(const std::vector<const char *> &tokens)
{
	// TODO: sanity check tokens.

	Instruction i = instructions[tokens[0]];
	isa32::word_t opcode = i.opcode;
	isa32::word_t rs = registers[tokens[1]];
	isa32::word_t rt = registers[tokens[2]];
	isa32::word_t funct = i.funct;

	isa32::word_t inst = 0;
	inst |= (opcode & INST_MASK_OPCODE) << INST_SHIFT_OPCODE;
	inst |= (rs & INST_MASK_RS) << INST_SHIFT_RS;
	inst |= (rt & INST_MASK_RT) << INST_SHIFT_RT;
	inst |= (funct & INST_MASK_FUNCT) << INST_SHIFT_FUNCT;

	return (inst);
}

/**
 * @brief Encodes jr R-type instruction.
 *
 * @param tokens Instruction tokens.
 *
 * @returns The encoded instruction.
 */
static isa32::word_t encode_instruction_R_jr(const std::vector<const char *> &tokens)
{
	// TODO: sanity check tokens.

	Instruction i = instructions[tokens[0]];
	isa32::word_t opcode = i.opcode;
	isa32::word_t rs = registers[tokens[1]];
	isa32::word_t funct = i.funct;

	isa32::word_t inst = 0;
	inst |= (opcode & INST_MASK_OPCODE) << INST_SHIFT_OPCODE;
	inst |= (rs & INST_MASK_RS) << INST_SHIFT_RS;
	inst |= (funct & INST_MASK_FUNCT) << INST_SHIFT_FUNCT;

	return (inst);
}

/**
 * @brief Encodes an I-type instruction.
 *
 * @param tokens Instruction tokens.
 *
 * @returns The encoded instruction.
 */
static isa32::word_t encode_instruction_I_generic(const std::vector<const char *> &tokens)
{
	// TODO: sanity check tokens.

	Instruction i = instructions[tokens[0]];
	isa32::word_t opcode = i.opcode;
	isa32::word_t rt = registers[tokens[1]];
	isa32::word_t rs = registers[tokens[2]];
	isa32::word_t imm = strtoul(tokens[3], NULL, 10);

	isa32::word_t inst = 0;
	inst |= (opcode & INST_MASK_OPCODE) << INST_SHIFT_OPCODE;
	inst |= (rt & INST_MASK_RT) << INST_SHIFT_RT;
	inst |= (rs & INST_MASK_RS) << INST_SHIFT_RS;
	inst |= (imm & INST_MASK_IMM) << INST_SHIFT_IMM;

	return (inst);
}

/**
 * @brief Encodes a lw/sw I-type instruction.
 *
 * @param tokens Instruction tokens.
 *
 * @returns The encoded instruction.
 */
static isa32::word_t encode_instruction_I_ls(const std::vector<const char *> &tokens)
{
	// TODO: sanity check tokens.

	Instruction i = instructions[tokens[0]];
	isa32::word_t opcode = i.opcode;
	isa32::word_t imm = strtoul(tokens[2], NULL, 10);
	isa32::word_t rs = registers[tokens[3]];
	isa32::word_t rd = registers[tokens[1]];

	isa32::word_t inst = 0;
	inst |= (opcode & INST_MASK_OPCODE) << INST_SHIFT_OPCODE;
	inst |= (rs & INST_MASK_RS) << INST_SHIFT_RS;
	inst |= (rd & INST_MASK_RD) << INST_SHIFT_RD;
	inst |= (imm & INST_MASK_IMM) << INST_SHIFT_IMM;

	return (inst);
}

/**
 * @brief Encodes a J-type instruction.
 *
 * @param tokens Instruction tokens.
 *
 * @returns The encoded instruction.
 */
static isa32::word_t encode_instruction_J_generic(const std::vector<const char *> &tokens)
{
	// TODO: sanity check tokens.

	Instruction i = instructions[tokens[0]];
	isa32::word_t opcode = i.opcode;
	isa32::word_t target = strtoul(tokens[1], NULL, 10);

	isa32::word_t inst = 0;
	inst |= (opcode & INST_MASK_OPCODE) << INST_SHIFT_OPCODE;
	inst |= (target & INST_MASK_TARGET) << INST_SHIFT_TARGET;

	return (inst);
}

// Encodes an instruction.
isa32::word_t Mips32Assembler::encode_instruction(const std::vector<const char *> &tokens)
{
	Instruction i = instructions[tokens[0]];

	return (i.encode(tokens));
}