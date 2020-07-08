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

#include <assert.h>
#include <stdint.h>
#include "../test_mips32.h"

#define TEST_ASSSEMBLER_VERBOSE 0

PRIVATE void assertEquals(uint32_t expected_instruction, uint32_t real_instruction){
	assert(expected_instruction == real_instruction);
}

PRIVATE void test_parse_Uint32(void){
	assertEquals(parseUint32_t("001", 3), 1);
}

PRIVATE void test_encode_r_instruction(void){
	const char *instr = "add s0, s1, s2";

	assertEquals(encode_r_instruction(instr), 0);
}

PRIVATE void test_encode_mult(void){
	const char *instr = "mult s0, s1"
	
	assertEquals(encode_mult(instr), 0);
}

PRIVATE void test_encode_div(void){
	const char *instr = "div s0, s1";

	assertEquals(encode_div(instr), 0);
}

PRIVATE void test_encode_sll(void){
	const char *instr = "sll s0, s1, 1";

	assertEquals(encode_sll(instr), 0);
}

PRIVATE void test_encode_srl(void){
	const char *instr = "sll s0, s1, 1";

	assertEquals(encode_srl(instr), 0);
}

PRIVATE void test_encode_jr(void){
	const char *instr = "jr s0";

	assertEquals(encode_jr(instr), 0);
}

PRIVATE void test_encode_i_instruction(void){
	const char *instr = "addi s0, s1, 1";

	assertEquals(encode_i_instruction(instr), 0);
}

PRIVATE void test_encode_lw(void){
	const char *instr = "lw s0, 4(s1)";

	assertEquals(encode_lw(instr), 0);
}

PRIVATE void test_encode_sw(void){
	const char *instr = "sw s0, 4(s1)";

	assertEquals(encode_sw(instr), 0);
}

PRIVATE void test_encode_j(void){

}

PRIVATE struct test mips32_tests_api[] = {
	{ test_parse_Uint32,         "Parse binary string to uint32"},
	{ test_encode_r_instruction, "Encode generic r instruction" },
	{ test_encode_mult,          "Encode mult instruction"      },
	{ test_encode_div,           "Encode div instruction"       },
	{ test_encode_sll,           "Encode sll instruction"       },
	{ test_encode_srl,           "Encode srl instruction"       },
	{ test_encode_jr,            "Encode jr instruction"        },
	{ test_encode_i_instruction, "Encode generic i instruction" },
	{ test_encode_lw,            "Encode lw instruction"        },
	{ test_encode_sw,            "Encode sw instruction"        },
	{ test_encode_j,             "Encode j instruction"         },
	{ NULL,                       NULL                          },
};

PUBLIC void test_mips32 (void){
	printf(HLINE);

	for(int i = 0; mips32_tests_api != NULL; i++){
		mips32_tests_api[i].test_fn();
#if(TEST_ASSSEMBLER_VERBOSE)		
		printf("[assembler][mips 32][api] %s [passed]", mips32_tests_api[i].name);
#endif	
	}
}
