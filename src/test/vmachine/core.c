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
#include "../test.h"

#define VMACHINE_INSTRUCTION_RD 0x0000f800
#define VMACHINE_INSTRUCTION_SHIFT_RD 8

/* Functions prototypes */
extern char instruction_type(uint32_t opcode);
extern void do_execute_R(uint32_t instruction);
extern void do_execute_I(uint32_t instruction);
extern void do_execute_J(uint32_t instruction);
extern uint32_t get_registers(int regnum);

void test_instruction_type(void) {
	uint32_t opcode = 0x00;
	assert(instruction_type(opcode) == 'R');
}

void test_do_execute_R(void) {
	uint32_t instruction = 104444042;

	int rd = instruction & VMACHINE_INSTRUCTION_RD;
	rd = rd >> VMACHINE_INSTRUCTION_SHIFT_RD;
	
	do_execute_R(instruction);
	assert(get_registers(rd) == 0x09);
}

void test_do_execute_I(void) {
	/* TO DO */
}

void test_do_execute_J(void) {
	/* TO DO */
}

struct test core_tests_api[] = {
	{ test_instruction_type, 	"Define instruction type"		},
	{ test_do_execute_R,		"Execute a R-type instruction"	},
	{ test_do_execute_I,		"Execute a I-type instruction"	},
	{ test_do_execute_J,		"Execute a J-type instruction"	},
	{ NULL,			 NULL					}
};

void test_core (void){
	for(int i = 0; core_tests_api != NULL; i++){
		core_tests_api[i].test_fn();
		printf("[vmachine][core][api] %s [passed]", core_tests_api[i].name);
	}
}

#endif
