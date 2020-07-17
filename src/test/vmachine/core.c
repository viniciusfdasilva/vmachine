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

#include <stdio.h>
#include <assert.h>

/* Functions prototypes */
extern char instruction_type(uint32_t opcode);
extern void do_execute_R(uint32_t instruction);
extern void do_decode(uint32_t instruction);

void test_intruction_type(void) {
	/* TO DO */
}

void test_do_execute_R(void) {
	/* TO DO */
}

void test_do_decode(void) {
	/* TO DO */
}

struct test core_tests_api[] = {
	{ test_instruction_type, "Define instruction type" 	},
	{ test_do_execute_R, 	 "Execute a R-type instruction"	},
	{ test_do_decode, 	 "Decode a instruction" 	},
	{ NULL,			 NULL				}
};

void test_core (void){
	for(int i = 0; core_tests_api != NULL; i++){
		/* TO DO */
	}
}
