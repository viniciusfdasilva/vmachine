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
#include <string>
#include <list>

// Ours
#include <asm/mips32.h>
#include <arch/mips32.h>
#include <test.h>

using namespace mips32;

bool test_encode_r_generic(void)
{
	Mips32Assembler a;
	std::string instr = "add s0, s1, s2";

	isa32::word_t want =
		(INST_OPCODE_ADD << INST_SHIFT_OPCODE) |
		(REG_S1 << INST_SHIFT_RS)              |
		(REG_S2 << INST_SHIFT_RT)              |
		(REG_S0 << INST_SHIFT_RD)              |
		(0 << INST_SHIFT_SHAMT)                |
		(INST_FUNCT_ADD << INST_SHIFT_FUNCT);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_mult(void)
{
	Mips32Assembler a;
	std::string instr = "mult s0, s1";

	isa32::word_t want =
		(INST_OPCODE_MULT << INST_SHIFT_OPCODE) |
		(REG_S0 << INST_SHIFT_RS)               |
		(REG_S1 << INST_SHIFT_RT)               |
		(0 << INST_SHIFT_RD)                    |
		(0 << INST_SHIFT_SHAMT)                 |
		(INST_FUNCT_MULT << INST_SHIFT_FUNCT);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_div(void)
{
	Mips32Assembler a;
	std::string instr = "div s0, s1";

	isa32::word_t want =
		(INST_OPCODE_DIV << INST_SHIFT_OPCODE) |
		(REG_S0 << INST_SHIFT_RS)              |
		(REG_S1 << INST_SHIFT_RT)              |
		(0 << INST_SHIFT_RD)                   |
		(0 << INST_SHIFT_SHAMT)                |
		(INST_FUNCT_DIV << INST_SHIFT_FUNCT);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_sll(void)
{
	Mips32Assembler a;
	std::string instr = "sll s0, s1, 1";

	isa32::word_t want =
		(INST_OPCODE_SLL << INST_SHIFT_OPCODE)    |
		(0 << INST_SHIFT_RS)                      |
		(REG_S1 << INST_SHIFT_RT)                 |
		(REG_S0 << INST_SHIFT_RD)                 |
		(1 << INST_SHIFT_SHAMT)                   |
		(INST_FUNCT_SLL << INST_SHIFT_FUNCT);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_srl(void)
{
	Mips32Assembler a;
	std::string instr = "srl s0, s1, 1";

	isa32::word_t want =
		(INST_OPCODE_SRL << INST_SHIFT_OPCODE)    |
		(0 << INST_SHIFT_RS)                      |
		(REG_S1 << INST_SHIFT_RT)                 |
		(REG_S0 << INST_SHIFT_RD)                 |
		(1 << INST_SHIFT_SHAMT)                   |
		(INST_FUNCT_SRL << INST_SHIFT_FUNCT);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_jr(void)
{
	Mips32Assembler a;
	std::string instr = "jr s0";

	isa32::word_t want =
		(INST_OPCODE_JR << INST_SHIFT_OPCODE)   |
		(REG_S0 << INST_SHIFT_RS)               |
		(0 << INST_SHIFT_RT)                    |
		(0 << INST_SHIFT_RD)                    |
		(0 << INST_SHIFT_SHAMT)                 |
		(INST_FUNCT_JR << INST_SHIFT_FUNCT);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_i_generic(void)
{
	Mips32Assembler a;
	std::string instr = "addi s0, s1, 1";

	isa32::word_t want =
		(INST_OPCODE_ADDI << INST_SHIFT_OPCODE) |
		(REG_S0 << INST_SHIFT_RT)               |
		(REG_S1 << INST_SHIFT_RS)               |
		(1 << INST_SHIFT_IMM);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_lw(void)
{
	Mips32Assembler a;
	std::string instr = "lw s0, 4(s1)";

	isa32::word_t want =
		(INST_OPCODE_LW << INST_SHIFT_OPCODE) |
		(REG_S1 << INST_SHIFT_RS)             |
		(REG_S0 << INST_SHIFT_RD)             |
		(4 << INST_SHIFT_IMM);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_sw(void)
{
	Mips32Assembler a;
	std::string instr = "sw s0, 4(s1)";

	isa32::word_t want =
		(INST_OPCODE_SW << INST_SHIFT_OPCODE) |
		(REG_S1 << INST_SHIFT_RS)             |
		(REG_S0 << INST_SHIFT_RD)             |
		(4 << INST_SHIFT_IMM);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

bool test_encode_j_generic(void)
{
	Mips32Assembler a;
	std::string instr = "j 1024";

	isa32::word_t want =
		(INST_OPCODE_J << INST_SHIFT_OPCODE) |
		(1024 << INST_SHIFT_TARGET);

	isa32::word_t have = a.assembly(instr);

	return (assertEquals(want, have));
}

std::list<test::Test *> mips32AssemblerTests(void)
{
	test::Test *t;
	std::list<test::Test *> tests;

	t = new test::Test("r-type generic", test_encode_r_generic);
	tests.push_back(t);
	t = new test::Test("div", test_encode_div);
	tests.push_back(t);
	t = new test::Test("mult", test_encode_mult);
	tests.push_back(t);
	t = new test::Test("sll", test_encode_sll);
	tests.push_back(t);
	t = new test::Test("srl", test_encode_srl);
	tests.push_back(t);
	t = new test::Test("jr", test_encode_jr);
	tests.push_back(t);
	t = new test::Test("lw", test_encode_lw);
	tests.push_back(t);
	t = new test::Test("sw", test_encode_sw);
	tests.push_back(t);
	t = new test::Test("i-type generic", test_encode_i_generic);
	tests.push_back(t);
	t = new test::Test("j-type generic", test_encode_j_generic);
	tests.push_back(t);

	return (tests);
}