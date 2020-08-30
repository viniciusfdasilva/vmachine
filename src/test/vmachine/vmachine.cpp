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
#include <vmachine.h>
#include <test.h>

using namespace vmachine;

bool test_execute_R(void)
{
	isa32::word_t inst =
		(INST_OPCODE_NOR << INST_SHIFT_OPCODE) |
		(REG_18 << INST_SHIFT_RS)              |
		(REG_17 << INST_SHIFT_RT)              |
		(REG_16 << INST_SHIFT_RD)              |
		(0 << INST_SHIFT_SHAMT)                |
		(INST_FUNCT_NOR << INST_SHIFT_FUNCT);

	ICache icache(VMACHINE_DEFAULT_CACHE_SIZE);
	DCache dcache(VMACHINE_DEFAULT_CACHE_SIZE);
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	VMachine vm(
		icache,
		dcache,
		memory
	);
	
	vm.execute(inst);

	return (assertEquals(vm.getRegister(REG_16), 0xffffffff));
}

bool test_execute_I(void)
{
	isa32::word_t inst =
		(INST_OPCODE_ADDI << INST_SHIFT_OPCODE) |
		(REG_16 << INST_SHIFT_RS)               |
		(REG_17 << INST_SHIFT_RT)               |
		(1 << INST_SHIFT_IMM);

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
		(INST_OPCODE_J << INST_SHIFT_OPCODE) |
		(0x1e << INST_SHIFT_TARGET);

	ICache icache(VMACHINE_DEFAULT_CACHE_SIZE);
	DCache dcache(VMACHINE_DEFAULT_CACHE_SIZE);
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	VMachine vm(
		icache,
		dcache,
		memory
	);
	
	vm.execute(inst);

	return (assertEquals(vm.getPC(), 0x1e << 2));
}

std::list<test::Test *> vmachineTests(void)
{
	test::Test *t;
	std::list<test::Test *> tests;

	t = new test::Test("execute r-type instruction", test_execute_R);
	tests.push_back(t);
	t = new test::Test("execute i-type instruction", test_execute_I);
	tests.push_back(t);
	t = new test::Test("execute J-type instruction", test_execute_J);
	tests.push_back(t);

	return (tests);
}