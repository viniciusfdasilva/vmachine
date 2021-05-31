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

#ifndef BENCHMARCK_INSTRUCTIONS_BANK_H_
#define BENCHMARCK_INSTRUCTIONS_BANK_H_

namespace instructions_bank
{
    #define INSTRUCTIONS_NUMS 37

    /**
	 * @name Instructions examples bank
	 */
	/**@{*/
 
    // R-Type
    #define ADD   0x718033
    #define SUB   0x40408033
    #define SLL   0x5114b3
    #define SLT   0x122433
    #define SLTU  0x643233
    #define XOR   0x33c0b3
    #define SRL   0x5353b3
    #define SRA   0x4082d4b3
    #define OR    0x91e333
    #define AND   0xa0f5b3

    // I-Type
    #define JALR  0x6a52826f
    #define LB    0x78508103
    #define LH    0x15401083
    #define LW    0x65d6a183
    #define LBU   0x5653c283
    #define LHU   0x2a94d383
    #define ADDI  0x92958013
    #define SLTI  0x55512093
    #define SLTIU 0xf150b193
    #define XORI  0x1cb1c493
    #define PRI   0x6ab3e213
    #define ANDI  0xed527313
    #define SLLI  0x101193
    #define SRLI  0x325293
    #define SRAI  0x40435393

    // U-Type
    #define LUI   0xaaf1d237
    #define AUIPC 0xcd7e6097

    // J-Type
    #define JAL   0xc9e2906f

    // S-type
    #define SB    0x94208923
    #define SH    0xba339aa3
    #define SW    0xb654aca3

    // B-Type
    #define BEQ   0x34020963
    #define BNE   0x9c119ce3
    #define BLT   0x5020c263
    #define BGE   0x9033dee3
    #define BLTU  0x32546be3
    #define BGEU  0x5461fc63

    /**@}*/
}

#endif // BENCHMARCK_INSTRUCTIONS_BANK_H_