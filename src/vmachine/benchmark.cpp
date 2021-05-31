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

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>

#include "instruction_bank.h"
#include <arch.h>
#include <vmachine/isa.h>
#include <vmachine/core.h>
#include <vmachine/memory.h>
#include <vmachine/benchmark.h>
#include <config.h>

using namespace vmachine;

// Instructions Array
isa32::word_t instructions[INSTRUCTIONS_NUMS] = {
    ADD,
    SUB,
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
    JALR,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    PRI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
    LUI,
    AUIPC,
    JAL,
    SB,
    SH,
    SW,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU
};

// Get how many times each type was executed
int r_type_quantity;
int i_type_quantity;
int s_type_quantity;
int u_type_quantity;
int b_type_quantity;
int j_type_quantity;

// Separates instructions by type and count
void Benchmark::counts_type(isa32::word_t instruction) {
	isa32::word_t opcode;

	opcode = instruction & INST_MASK_OPCODE;

	switch(opcode)
	{
		// U-Type Instruction
		case U_TYPE_IMMEDIATE_INSTRUCTION:
		case U_TYPE_PC_INSTRUCTION:
			u_type_quantity ++;
		break;

		// B-Type Instruction
		case B_TYPE_INSTRUCTIONS:
			b_type_quantity ++;
		break;

		// S-Type Instruction
		case S_TYPE_INSTRUCTIONS:
			s_type_quantity ++;
		break;

		// R-Type Instruction
		case R_TYPE_INSTRUCTIONS:
			r_type_quantity ++;
		break;

		// J-Type Instruction
		case J_TYPE_INSTRUCTION:
			j_type_quantity ++;
		break;

		// I-Type Instruction
		default:
			i_type_quantity ++;
		break;
	}
}

// Runs instruction on vmachine's core
void Benchmark::run(isa32::word_t instruction) {
	Memory memory(VMACHINE_DEFAULT_MEMORY_SIZE);

	Core core(memory);

	auto start = std::chrono::high_resolution_clock::now();
		core.execute(instruction);
	auto end = std::chrono::high_resolution_clock::now() - start;

	counts_type(instruction);	
}

// int main() {
// 	int inst_quantity = 0;

	//std::cout << "How many functions to perform? ";
	//std::cin >> inst_quantity;

	// faz inst_quantity buscas aleatórias no array de instruções
	
	//auto start = std::chrono::high_resolution_clock::now();
	// TO DO
	// Run core


    	//for (int i = 0; i < inst_quantity; i++) {
	//	int random_number = rand() % INSTRUCTIONS_NUMS - 0;
		
		//Core::execute(instructions[random_number]);
        //	counts_type(instructions[random_number]);
    	//}

	//auto end = std::chrono::high_resolution_clock::now() - start;

    // 	std::cout << "\nR-Type: ";
    // 	std::cout << r_type_quantity;
	// std::cout << " functions executed.\nI-Type: ";
	// std::cout << i_type_quantity;
	// std::cout << " functions executed.\nJ-Type: ";
	// std::cout << j_type_quantity;
	// std::cout << " functions executed.\nU-Type: ";
	// std::cout << u_type_quantity;
	// std::cout << " functions executed.\nB-Type: ";
	// std::cout << b_type_quantity;
	// std::cout << " functions executed.\nS-Type: ";
	// std::cout << s_type_quantity;
	// std::cout << " functions executed.\n";

	//long long nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();

	//std::cout << "\nTime spent: " << nanoseconds << " nanoseconds.\n";

// 	std::cout << "\nTotal functions performed: " << inst_quantity << "\n";
// }


