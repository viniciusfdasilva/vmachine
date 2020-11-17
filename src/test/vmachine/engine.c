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

#ifndef NDEBUG

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include "../test.h"
#include <../include/vmachine/engine.h>

/* Import definitions. */
extern void test_engine_add(void);
extern void test_engine_addu(void);
extern void test_engine_sub(void);
extern void test_engine_subu(void);
extern void test_engine_div(void);
extern void test_engine_divu(void);
extern void test_engine_mult(void);
extern void test_engine_multu(void);
extern void test_engine_jr(void);
extern void test_engine_and(void);
extern void test_engine_nor(void);
extern void test_engine_or(void);
extern void test_engine_slt(void);
extern void test_engine_sltu(void);
extern void test_engine_sll(void);
extern void test_engine_srl(void);
extern void test_engine_sra(void);

#define assertEquals(x, y) assert((x) == (y))

void test_engine_add(void){
	// add $s0,$s1,$s2
	assertEquals(engine_run(36864032),19433523);
}

void test_engine_addu(void){
	// addu $s0,$s1,$s2
	assertEquals(engine_run(36864033),19433523);
}

void test_engine_sub(void){
	// sub $s0,$s1,$s2
	assertEquals(engine_run(36864034),1093175347);
}

void test_engine_subu(void){
	// subu $s0,$s1,$s2
	assertEquals(engine_run(36864035),1093175347);
}

void test_engine_div(void){
	// div $s0,$s1
	assertEquals(engine_run(34668570),51922611);
}

void test_engine_divu(void){
	// divu $s0,$s1
	assertEquals(engine_run(34668571),51926707);
}

void test_engine_mult(void){
	// mult $s0,$s1
	assertEquals(engine_run(34668568),51906227);
}

void test_engine_multu(void){
	// multu $s0,$s1
	assertEquals(engine_run(34668569),51906227);
}

void test_engine_jr(void){
	// jr ra
	assertEquals(engine_run(65011720),4071);
}

void test_engine_and(void){
	// and $s0,$s1,$s2
	assertEquals(engine_run(36864036),19462195);
}

void test_engine_nor(void){
	// nor $s0,$s1,$s2
	//assertEquals(engine_run(36864039),0);
}

void test_engine_or(void){
	// or $s0,$s1,$s2
	assertEquals(engine_run(36864037),19458099);
}

void test_engine_slt(void){
	// slt $s0,$s1,$s2
	assertEquals(engine_run(36864042),19441715);
}

void test_engine_sltu(void){
	// sltu $s0,$s1,$s2
	assertEquals(engine_run(36864043),19445811);
}

void test_engine_sll(void){
	// sll $s0,$s1,0xA
	assertEquals(engine_run(1147520),18257971);
}

void test_engine_srl(void){
	// srl $s0,$s1,0xA
	assertEquals(engine_run(1147522),18274355);
}

void test_engine_sra(void){
	// sra $s0,$s1,0xA
	assertEquals(engine_run(1147523),1092016179);
}

struct test engine_tests_api[] = {
	{test_engine_add,    "Tranlate MIPS add to RISC-V"  },
	{test_engine_addu,   "Tranlate MIPS addu to RISC-V" },
	{test_engine_sub,    "Tranlate MIPS sub to RISC-V"  },
	{test_engine_div,    "Tranlate MIPS div to RISC-V"  },
	{test_engine_divu,   "Tranlate MIPS divu to RISC-V" },
	{test_engine_mult,   "Tranlate MIPS mult to RISC-V" },
	{test_engine_multu,  "Tranlate MIPS multu to RISC-V"},
	{test_engine_jr,     "Tranlate MIPS jr to RISC-V"   },
	{test_engine_and,    "Tranlate MIPS and to RISC-V"  },
	{test_engine_nor,    "Tranlate MIPS nor to RISC-V"  },
	{test_engine_or,     "Tranlate MIPS or to RISC-V"   },
	{test_engine_slt,    "Tranlate MIPS slt to RISC-V"  },
	{test_engine_sltu,   "Tranlate MIPS sltu to RISC-V" },
	{test_engine_sll,    "Tranlate MIPS sll to RISC-V"  },
	{test_engine_srl,    "Tranlate MIPS srl to RISC-V"  },
	{test_engine_sra,    "Tranlate MIPS sra to RISC-V"  },
	{      NULL     ,                 NULL              }
};

void test_engine(void)
{
	for(int i = 0; engine_tests_api != NULL; i++)
	{
		engine_tests_api[i].test_fn();
		printf("[vmachine][engine][api] %s [passed]\n", engine_tests_api[i].name);
	}
}

#endif /* !NDEBUG */
