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

#include <list>

#include <vmachine.h>
#include <test.h>
#include <vmachine/engine.h>

bool test_engine_add(void){
	Engine engine;

	// add $s0,$s1,$s2
	return assertEquals(engine.engine_run(36864032),19433523);
}

bool test_engine_addu(void){
	Engine engine;

	// addu $s0,$s1,$s2
	return assertEquals(engine.engine_run(36864033),19433523);
}

bool test_engine_sub(void){
	Engine engine;

	// sub $s0,$s1,$s2
	return assertEquals(engine.engine_run(36864034),1093175347);
}

bool test_engine_subu(void){
	Engine engine;
	
	// subu $s0,$s1,$s2
	return assertEquals(engine.engine_run(36864035),1093175347);
}

bool test_engine_jr(void){
	Engine engine;

	// jr ra
	return assertEquals(engine.engine_run(65011720),4071);
}

bool test_engine_and(void){
	Engine engine;

	// and $s0,$s1,$s2
	return assertEquals(engine.engine_run(36864036),19462195);
}

bool test_engine_nor(void){
	Engine engine;

	// nor $s0,$s1,$s2
	return assertEquals(engine.engine_run(36864039),0);
}

bool test_engine_or(void){
	Engine engine;

	// or $s0,$s1,$s2
	return 	assertEquals(engine.engine_run(36864037),19458099);
}

bool test_engine_slt(void){
	Engine engine;

	// slt $s0,$s1,$s2
	return assertEquals(engine.engine_run(36864042),19441715);
}

bool test_engine_sltu(void){
	Engine engine;

	// sltu $s0,$s1,$s2
	return assertEquals(engine.engine_run(36864043),19445811);
}

bool test_engine_sll(void){
	Engine engine;

	// sll $s0,$s1,0xA
	return assertEquals(engine.engine_run(1147520),18257971);
}

bool test_engine_srl(void){
	Engine engine;

	// srl $s0,$s1,0xA
	return assertEquals(engine.engine_run(1147522),18274355);
}

bool test_engine_sra(void){
	Engine engine;

	// sra $s0,$s1,0xA
	return assertEquals(engine.engine_run(1147523),1092016179);
}

bool test_engine_div(void){
	Engine engine;

	// div $s0,$s1
	return assertEquals(engine.engine_run(34668570),51922611);
}

bool test_engine_divu(void){
	Engine engine;

	// divu $s0,$s1
	return assertEquals(engine.engine_run(34668571),51926707);
}

bool test_engine_mult(void){
	Engine engine;

	// mult $s0,$s1
	return assertEquals(engine.engine_run(34668568),51906227);
}

bool test_engine_multu(void){
	Engine engine;

	// multu $s0,$s1
	return assertEquals(engine.engine_run(34668569),51906227);
}

std::list<test::Test *> engineTests(void)
{
	test::Test *t;
	std::list<test::Test *> tests;

    t = new test::Test("Tranlate MIPS add to RISC-V",test_engine_add);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS addu to RISC-V",test_engine_addu);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS sub to RISC-V",test_engine_sub);
	tests.push_back(t);
    t = new test::Test("Tranlate MIPS subu to RISC-V",test_engine_subu);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS jr to RISC-V",test_engine_jr);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS or to RISC-V",test_engine_or);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS and to RISC-V",test_engine_and);
	tests.push_back(t);	
	t = new test::Test("Tranlate MIPS slt to RISC-V",test_engine_slt);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS sltu to RISC-V",test_engine_sltu);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS sll to RISC-V",test_engine_sll);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS srl to RISC-V",test_engine_srl);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS sra to RISC-V",test_engine_sra);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS div to RISC-V",test_engine_div);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS divu to RISC-V",test_engine_divu);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS mult to RISC-V",test_engine_mult);
	tests.push_back(t);
	t = new test::Test("Tranlate MIPS multu to RISC-V",test_engine_multu);
	tests.push_back(t);
	

    return (tests);
}