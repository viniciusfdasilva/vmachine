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
#include <list>
#include <string>

// Ours
#include <config.h>
#include <test.h>
#include <arch.h>
#include <vmachine.h>

using namespace vmachine;

bool test_execute_R(void)
{
	isa32::word_t inst =
		(INST_XOR_FUNCT_7  << INST_SHIFT_FUNCT_7) |
		(INST_XOR_FUNCT_3  << INST_SHIFT_FUNCT_3) |
		(REG_18            << INST_SHIFT_RS_1)    |
		(REG_17            << INST_SHIFT_RS_2)    |
		(REG_16            << INST_SHIFT_RD)      |
		(R_TYPE_INSTRUCTIONS);

	ICache icache(VMACHINE_DEFAULT_CACHE_SIZE);
	DCache dcache(VMACHINE_DEFAULT_CACHE_SIZE);
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	VMachine vm(
		icache,
		dcache,
		memory
	);

	vm.execute(inst);

	return (assertEquals(vm.getRegister(REG_16), 0x00000000));
}

bool test_execute_I(void)
{
	isa32::word_t inst =
		(REG_16            << INST_SHIFT_RS_1)             |
		(REG_17            << INST_SHIFT_RD)               |
		(INST_ADDI_FUNCT_3 << INST_SHIFT_FUNCT_3)          |
		(1                 << INST_SHIFT_IMMEDIATE_I_TYPE) |
		(INST_OPCODE_ADDI);

	ICache icache(VMACHINE_DEFAULT_CACHE_SIZE);
	DCache dcache(VMACHINE_DEFAULT_CACHE_SIZE);
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	VMachine vm(
		icache,
		dcache,
		memory
	);

	vm.execute(inst);

	return (assertEquals(vm.getRegister(REG_17), 0x1));
}

bool test_execute_J(void)
{
	isa32::word_t inst =
		(INST_OPCODE_JAL)                       |
		(REG_8        << INST_SHIFT_RD)         |
		(0x1e         << INST_SHIFT_IMMEDIATE);

	ICache icache(VMACHINE_DEFAULT_CACHE_SIZE);
	DCache dcache(VMACHINE_DEFAULT_CACHE_SIZE);
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	VMachine vm(
		icache,
		dcache,
		memory
	);

	isa32::word_t pc_value = vm.getPC();
	vm.execute(inst);

	return (assertEquals(vm.getPC(), pc_value += 0x1e));
}

bool test_execute_S(void)
{
	isa32::word_t inst =
		(S_TYPE_INSTRUCTIONS)                   |
		(INST_SW_FUNCT_3 << INST_SHIFT_FUNCT_3) |
		(REG_16          << INST_SHIFT_RS_1)    |
		(REG_17          << INST_SHIFT_RS_2)    |
		(0x1e            << INST_SHIFT_FUNCT_7);

	ICache icache(VMACHINE_DEFAULT_CACHE_SIZE);
	DCache dcache(VMACHINE_DEFAULT_CACHE_SIZE);
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	VMachine vm(
		icache,
		dcache,
		memory
	);

	vm.execute(inst);

	return (assertEquals(memory.read(0x1e), 0x00));
}

bool test_execute_B(void)
{
	isa32::word_t inst =
		(B_TYPE_INSTRUCTIONS)                           |
		(INST_BEQ_FUNCT_3        << INST_SHIFT_FUNCT_3) |
		(REG_16                << INST_SHIFT_RS_1)      |
		(REG_17                << INST_SHIFT_RS_2)      |
		(0x1e                << INST_SHIFT_FUNCT_7);

	ICache icache(VMACHINE_DEFAULT_CACHE_SIZE);
	DCache dcache(VMACHINE_DEFAULT_CACHE_SIZE);
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	VMachine vm(
		icache,
		dcache,
		memory
	);

	isa32::word_t pc = vm.getPC();
	vm.execute(inst);

	return (assertEquals(vm.getPC(), pc + 0x1e));
}

bool test_execute_U(void)
{
	isa32::word_t inst =
		(INST_OPCODE_LUI)                              |
		(REG_16                << INST_SHIFT_RD)       |
		(0x1e                << INST_SHIFT_IMMEDIATE);

	ICache icache(VMACHINE_DEFAULT_CACHE_SIZE);
	DCache dcache(VMACHINE_DEFAULT_CACHE_SIZE);
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	VMachine vm(
		icache,
		dcache,
		memory
	);

	vm.execute(inst);

	return (assertEquals(vm.getRegister(REG_16), 0x1e << 12));
}

std::list<test::Test *> vmachineTests(void)
{
	test::Test *t;
	std::list<test::Test *> tests;

	t = new test::Test("execute R-type instruction", test_execute_R);
	tests.push_back(t);
	t = new test::Test("execute I-type instruction", test_execute_I);
	tests.push_back(t);
	t = new test::Test("execute J-type instruction", test_execute_J);
	tests.push_back(t);
	t = new test::Test("execute S-type instruction", test_execute_S);
	tests.push_back(t);
	t = new test::Test("execute B-type instruction", test_execute_B);
	tests.push_back(t);
	t = new test::Test("execute U-type instruction", test_execute_U);
	tests.push_back(t);

	return (tests);
}
