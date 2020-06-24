/*
 * MIT License
 *
 * Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
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

#ifndef MIPS32_REGS_H_
#define MIPS32_REGS_H_

	/**
	 * @brief Number of registers.
	 */
	#define REG_NUM 32

	/**
	 * @name Name of Registers
	 */
	/**@{*/
	#define REG_ZERO_NAME "zero"
	#define REG_AT_NAME   "at"
	#define REG_V0_NAME   "v0"
	#define REG_V1_NAME   "v1"
	#define REG_A0_NAME   "a0"
	#define REG_A1_NAME   "a1"
	#define REG_A2_NAME   "a2"
	#define REG_A3_NAME   "a3"
	#define REG_T0_NAME   "t0"
	#define REG_T1_NAME   "t1"
	#define REG_T2_NAME   "t2"
	#define REG_T3_NAME   "t3"
	#define REG_T4_NAME   "t4"
	#define REG_T5_NAME   "t5"
	#define REG_T6_NAME   "t6"
	#define REG_T7_NAME   "t7"
	#define REG_S0_NAME   "s0"
	#define REG_S1_NAME   "s1"
	#define REG_S2_NAME   "s2"
	#define REG_S3_NAME   "s3"
	#define REG_S4_NAME   "s4"
	#define REG_S5_NAME   "s5"
	#define REG_S6_NAME   "s6"
	#define REG_S7_NAME   "s7"
	#define REG_T8_NAME   "t8"
	#define REG_T9_NAME   "t9"
	#define REG_K0_NAME   "k0"
	#define REG_K1_NAME   "k1"
	#define REG_GP_NAME   "gp"
	#define REG_SP_NAME   "sp"
	#define REG_FP_NAME   "fp"
	#define REG_RA_NAME   "ra"
	/**@}*/

	/**
	 * @name Code of Registers (as string)
	 */
	/**@{*/
	#define REG_ZERO_NUM_STR  "00000"
	#define REG_AT_NUM_STR    "00001"
	#define REG_V0_NUM_STR    "00010"
	#define REG_V1_NUM_STR    "00011"
	#define REG_A0_NUM_STR    "00100"
	#define REG_A1_NUM_STR    "00101"
	#define REG_A2_NUM_STR    "00110"
	#define REG_A3_NUM_STR    "00111"
	#define REG_T0_NUM_STR    "01000"
	#define REG_T1_NUM_STR    "01001"
	#define REG_T2_NUM_STR    "01010"
	#define REG_T3_NUM_STR    "01011"
	#define REG_T4_NUM_STR    "01100"
	#define REG_T5_NUM_STR    "01101"
	#define REG_T6_NUM_STR    "01110"
	#define REG_T7_NUM_STR    "01111"
	#define REG_S0_NUM_STR    "10000"
	#define REG_S1_NUM_STR    "10001"
	#define REG_S2_NUM_STR    "10010"
	#define REG_S3_NUM_STR    "10011"
	#define REG_S4_NUM_STR    "10100"
	#define REG_S5_NUM_STR    "10101"
	#define REG_S6_NUM_STR    "10110"
	#define REG_S7_NUM_STR    "10111"
	#define REG_T8_NUM_STR    "11000"
	#define REG_T9_NUM_STR    "11001"
	#define REG_K0_NUM_STR    "11010"
	#define REG_K1_NUM_STR    "11011"
	#define REG_GP_NUM_STR    "11100"
	#define REG_SP_NUM_STR    "11101"
	#define REG_FP_NUM_STR    "11110"
	#define REG_RA_NUM_STR    "11111"
	/**@}**/

	/**
	 * @brief Register information.
	 */
	struct reg
	{
		const char *code;  /**< Register Code */
		const char *name;  /**< Register Name */
	};

#endif /* MIPS32_REGS_H_ */
