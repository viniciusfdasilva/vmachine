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
*
* Free Context Grammar of R types MIPS' 32 bits instructions
* 
* G:
*
* S → “0x00 [opcode]” [0] Format Function       
* Function → Arithmetic | UncJump | Logic | ConJump | Shift 
* Arithmetic → Sum | Sub | Mult | Div
* Sum → “0x20 [add]”[1][24] | “0x21 [addu]”[1][24]
* Sub→ “0x22 [sub]”[4][24] | “0x23 [subu]”[4][24]
* Div → “0x1a‬ [div]”[5][24][28] | “0x1b [divu]”[6][24][28]
* Mult → “0x18 [mult]”[7][24][28] | “0x19 [multu]”[7][24][28]
* UncJump → “0x08 [jr][26][27]”
* Logic → “0x24 [and]”[8][24] | “0x27 [nor]”[9][24] | “0x25 [or]”[10][24]
* ConJump → “0x2a [slt]”[11][24] | “0x29 [sltu]”[12][24]
* Shift → “0x00 [sll]”[13][24][28] | “0x02 [srl]”[14][24][28] | “0x03 [sra]”[15[24][28]
* Format → “[0x00-0x1f] [(rs | 0x00)]”[19] B
* B → “0x00 [shamt]” | “[0x00-0x1f] [rt][22]” C
* C → “0x00 [shamt]” | “[0x00-0x1f] [rd][21]” D
* D →  “0x00 [shamt]” | “[0x00-0x1f] [sa][23][25]”
*
* Translation scheme from MIPS32 to RV32
*
* [0] {se funct = "" entao S.opcode := "0x67" senao S.opcode := “0x33”}
* [1] {Sum.opfunct7 := “0x00”, Sum.opfunct3 := “0x00”}
* [2] {C.rs1 := rs.value}
* [3] {C.rs2 := rt.value}
* [4] {Sub.opfunct7 := “0x20”, Sub.opfunct3 := “0x00”}
* [5] {Div.opfunct7 := “0x01”, Div.opfunct3 := “0x04”}
* [6] {Div.opfunct7 := “0x01”, Div.opfunct3 := “0x05”}
* [7] {Mult.opfunct7 := “0x01”, Mult.opfunct3 := “0x00”}
* [8] {Logic.opfunct7 := “0x00”, Logic.opfunct3 := “0x07”}
* [9] {Logic.opfunct7 := “0x00”, Logic.opfunct3 := “0x00”}
* [10] {Logic.opfunct7 := “0x00”, Logic.opfunct3 := “0x06”}
* [11] {ConJump.opfunct7 := “0x00”, ConJump.opfunct3 := “0x02”}
* [12] {ConJump.opfunct7 := “0x00”, ConJump.opfunct3 := “0x03’”}
* [13] {Shift.opfunct7 := “0x00”, Shift.opfunct3 := “0x01”}
* [14] {Shift.opfunct7 := “0x00”, Shift.opfunct3 := “0x05”}
* [15] {Shift.opfunct7 := “0x20”, Shift.opfunct3 := “0x06”}
* [16] {Shift.function7 := “0x20”, Shift.opfunct3 := “0x06”}
* [15] {Shift.opfunct7 := “0x20”, Shift.opfunct3 := “0x06”}
* [18] {Shift.opfunct7 := “0x20”, Shift.opfunct3 := “0x06”}
* [19] {Format_rs := rs.lex}
* [21] {C_rd := rd.lex}
* [22] {B_rt := rt.lex}
* [23] {D_sa := sa.lex}
* [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
* [25] {rv_instructionAdd := “bin_n(D_sa) + 0x00 + 0x00 + (register) 0x13”}
* [26] {UncJump_funct3 = "0x00"}
* [27] {rv_instruction := 0x00 + 0x00(x0 = $zero) + 0x00 0x1f(x1 = ra) + opcode}
* [28] {rv_instructionAddi := 0x00 + (use_register) + 0x13}
*/
#include <vmachine/engine.h>
#include <arch/mips32.h>
#include <utils.h>

#include <iostream>
#include <string>

using namespace std;

// INSTRUCTION FORMAT: [SPECIAL	rs | rt | rd (ADD | SUB | AND | NOR | OR | SLT | SLTU)]
#define check_main_format(x) (check_addsub(x) | check_logic(x) | check_conJump(x))
// INSTRUCTION FORMAT: [SPECIAL	| rs | 0 | JR]
#define check_jr_format(x) x == INST_FUNCT_JR
// INSTRUCTION FORMAT: [SPECIAL	rs | rt | 0 | (DIV | DIVU | MULT | MULTU)]
#define check_divmul_format(x) check_divmul(x)
// INSTRUCTION FORMAT: [SPECIAL | 0 | rt | rd | sa | (SLL | SLR | SRA)]
#define check_shift_format(x) check_shift(x)

#define check_add_funct(x) (x == INST_FUNCT_ADD) || (x == INST_FUNCT_ADDU)
#define check_sub_funct(x) (x == INST_FUNCT_SUB) || (x == INST_FUNCT_SUBU)
#define check_logic(k) (k == INST_FUNCT_AND || k == INST_FUNCT_NOR || k == INST_FUNCT_OR)
#define check_addsub(x) check_add_funct(x) | check_sub_funct(x)
#define check_shamtRd(x) (x == 0x00 && (mips32_r_instruction.getRd().getCode() == NIL))
#define check_shamt(x) (x == 0x00 && (mips32_r_instruction.getRt().getCode() == NIL && mips32_r_instruction.getRd().getCode() == NIL))
#define check_shift(x) (x==INST_FUNCT_SLL || x==INST_FUNCT_SRL || x==INST_FUNCT_SRA)
#define check_conJump(x) (x==INST_FUNCT_SLT || x==INST_FUNCT_SLTU)
#define check_div(x) (x==INST_FUNCT_DIV || x==INST_FUNCT_DIVU)
#define check_mul(x) (x==INST_FUNCT_MULT || x==INST_FUNCT_MULTU)
#define check_divmul(x) check_div(x) | check_mul(x)



#define RV32_NOP 19 // addi x0,x0,0

#define NIL 0xffffffff

#define ARCH_MIPS32 32
#define INTEGER_BASE 10
#define MIPS32_REGISTERS 32
#define BINARY_BASE 2

#define SYNTATIC_ERROR "Syntatic Error!"

const isa32::word_t registers32[MIPS32_REGISTERS] = {
	REG_ZERO,
	REG_AT, REG_V0, REG_V1, 
	REG_A0, REG_A1, REG_A2,
	REG_A3, REG_T0, REG_T1,
	REG_T2, REG_T3, REG_T4,
	REG_T5, REG_T6, REG_T7,
	REG_S0, REG_S1, REG_S2,
	REG_S3, REG_S4, REG_S5,
	REG_S6, REG_S7, REG_T8,
	REG_T9, REG_K0, REG_K1,
	REG_GP, REG_SP, REG_FP,
	REG_RA,
};

/**
 * Check if these two parameters are equals.
 * @param tk1
 * @param tk2
 * */
void Engine::match(isa32::word_t token1,isa32::word_t token2)
{
    if(token1 != token2)
    {
        std::cout << "Syntatic Error! Between: " + to_string(token1) + " and " + to_string(token2) + " codes"; 
    }
}

/*
* r_procedure_D();
*/
void Engine::r_procedure_D()
{
    if(mips32_r_instruction.getInstruction().getShamt() == 0x00)
	{
		match(mips32_r_instruction.getInstruction().getShamt(),0x00);
	}else
	{
		match(mips32_r_instruction.getSa().getCode(),registers32[mips32_r_instruction.getSa().getCode()]);

		// Rule [23] {D_sa := sa.lex}
		D_sa = mips32_r_instruction.getSa().getCode();

		//[25] {rv_instructionAdd := “bin_n(D_sa) + "00000 000" + (register) 0010011”}
		// [CHECK ME]
		rv_instructionAdd |= (D_sa & 0x0000fff) << 20;
		rv_instructionAdd |= (0x00 & 0x000007f) << 15;
		rv_instructionAdd |= (0x00 & 0x0000007) << 12;
		rv_instructionAdd |= (use_register & 0x000001f) << 7;
		rv_instructionAdd |= (0x13 & 0x000007f) << 0;		
	}
}

/*
* r_procedure_C();
*/
void Engine::r_procedure_C()
{
    if(check_shamtRd(mips32_r_instruction.getInstruction().getShamt()))
	{
		match(mips32_r_instruction.getInstruction().getShamt(),0x00);
	}else
	{
		match(mips32_r_instruction.getRd().getCode(),registers32[mips32_r_instruction.getRd().getCode()]);

		// Rule [21] {C_rd := rd.lex}
		C_rd = mips32_r_instruction.getRd().getCode();

		r_procedure_D();
	}
}

/*
* r_procedure_B();
*/
void Engine::r_procedure_B()
{
	if(check_shamt(mips32_r_instruction.getInstruction().getShamt()))
	{
		match(mips32_r_instruction.getInstruction().getShamt(),0x00);
	}else
	{
		
		match(mips32_r_instruction.getRt().getCode(),registers32[mips32_r_instruction.getRt().getCode()]);

		// Rule [22] {B_rt := rt.lex}
		B_rt = mips32_r_instruction.getRt().getCode();

		r_procedure_C();
	}
}

/*
* r_procefure_Format()
*/
void Engine::r_procedure_Format()
{

	match(mips32_r_instruction.getRs().getCode(),registers32[mips32_r_instruction.getRs().getCode()]);
 
	// Rule [19] {Format_rs := rs.lex} 
	Format_rs = mips32_r_instruction.getRs().getCode();

	r_procedure_B();
} 

/**
 * r_pocedure_Sum(); 
 */
void Engine::r_procedure_Sum()
{
	if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_ADD)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_ADD);
	}else
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_ADDU);
	}

	// Rule [1] {Sum.funct7 := “0000000”, Sum.funct3 := “000”}
	Sum_funct7 = 0x00;
	Sum_funct3 = 0x00;

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}	
	rv_instruction = 0;
	rv_instruction |= (Sum_funct7 & 0x000007f) << 25;
	rv_instruction |= (B_rt & 0x000001f) << 20;
	rv_instruction |= (Format_rs & 0x000001f) << 15;
	rv_instruction |= (Sum_funct3 & 0x0000007) << 12;
	rv_instruction |= (C_rd & 0x000001f) << 7;
	rv_instruction |= (S_opcode & 0x000007f) << 0;

}

/**
 * r_pocedure_Sub(); 
 */
void Engine::r_procedure_Sub()
{
	if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_SUB)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_SUB);
	}else
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_SUBU);		
	}

	// Rule [4] {Sub.funct7 := “”, Sub.funct3 := “000”}
	Sub_funct7 = 0x20;
	Sub_funct3 = 0x00;
	
	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	rv_instruction = 0;	
	rv_instruction |= (Sub_funct7 & 0x000007f) << 25;
	rv_instruction |= (B_rt & 0x000001f) << 20;
	rv_instruction |= (Format_rs & 0x000001f) << 15;
	rv_instruction |= (Sub_funct3 & 0x0000007) << 12;
	rv_instruction |= (C_rd & 0x000001f) << 7;
	rv_instruction |= (S_opcode & 0x000007f) << 0;
}

/**
 * r_pocedure_Div(); 
 */
void Engine::r_procedure_Div()
{
	if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_DIV)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_DIV);

		// Rule [5] {Div.funct7 := “0000001”, Div.funct3 := “100”}
		Div_funct7 = 0x01;
		Div_funct3 = 0x04;
	
	}else
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_DIVU);

		// Rule [6] {Div.funct7 := “0000001”, Div.funct3 := “101”}
		Div_funct7 = 0x01; 
		Div_funct3 = 0x05;
	}
	
	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	rv_instruction = 0;	
	rv_instruction |= (Div_funct7 & 0x000007f) << 25;
	rv_instruction |= (B_rt & 0x000001f) << 20;
	rv_instruction |= (Format_rs & 0x000001f) << 15;
	rv_instruction |= (Div_funct3 & 0x0000007) << 12;
	rv_instruction |= (use_register & 0x000001f) << 7;
	rv_instruction |= (S_opcode & 0x000007f) << 0;

	// Rule [28] {rv_instructionAddi := 00000000000000000000 + (use_register) + 0010011}
	// Clean register using instruction [addi $use_register,x0,0x00]
	// [CHECK ME]
	rv_instructionAddi |= (0x00 & 0x00fffff) << 12;
	rv_instructionAddi |= (use_register & 0x000001f) << 7;
	rv_instructionAddi |= (0x13 & 0x000007f) << 0;
}

/**
 * r_pocedure_Mult();
 */
void Engine::r_procedure_Mult()
{
	if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_MULT)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_MULT);
	}else
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_MULTU);
	}

	// Rule [7] {Mult.funct7 := “0000001”, Mult.funct3 := “000”}
	Mult_funct7 = 0x01;
	Mult_funct3 = 0x00;

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	rv_instruction = 0;	
	rv_instruction |= (Mult_funct7 & 0x000007f) << 25;
	rv_instruction |= (B_rt & 0x000001f) << 20;
	rv_instruction |= (Format_rs & 0x000001f) << 15;
	rv_instruction |= (Mult_funct3 & 0x0000007) << 12;
	rv_instruction |= (use_register & 0x000001f) << 7;
	rv_instruction |= (S_opcode & 0x000007f) << 0;

	// Rule [28] {rv_instructionAddi := 00000000000000000000 + (use_register) + 0010011}
	// Clean register using instruction [addi $use_register,x0,0x00]
	// [CHECK ME]
	rv_instructionAddi |= (0x00 & 0x00fffff) << 12;
	rv_instructionAddi |= (use_register & 0x000001f) << 7;
	rv_instructionAddi |= (0x13 & 0x000007f) << 0;
}

/**
 * r_procedure_UncJump();
 */
void Engine::r_procedure_UncJump()
{
	match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_JR);

	// Rule [26] {UncJump_funct3 = "000"}
	UncJump_funct3 = 0x00;

	// Rule [27] {rv_instruction := 00000000000000000000 + 00000(x0 = $zero) + 000 11111(x1 = ra) + opcode}
	rv_instruction = 0;
	rv_instruction |= (0x00 & 0x0000fff) << 20;
	rv_instruction |= (0x00 & 0x000001f) << 15;
	rv_instruction |= (UncJump_funct3 & 0x000007) << 12;
	rv_instruction |= (Format_rs & 0x000001f) << 7;
	rv_instruction |= (S_opcode & 0x000007f) << 0;
}

/**
 * r_procedure_Logic();
 */
void Engine::r_procedure_Logic()
{
	if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_AND)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_AND);

		// Rule [8] {Logic.funct7 := “0000000”, Logic.funct3 := “111”}
		Logic_funct7 = 0x00; 
		Logic_funct3 = 0x07;
	}else if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_NOR)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_NOR);

		// Rule [9] {Logic.funct7 := “0000000”, Logic.funct3 := “000”}
		Logic_funct7 = 0x00;
		Logic_funct3 = 0x00;
	}else if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_OR)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_OR);

		// Rule [10] {Logic.funct7 := “0000000”, Logic.funct3 := “110”}
		Logic_funct7 = 0x00;
		Logic_funct3 = 0x06;
	}

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	rv_instruction = 0;
	rv_instruction |= (Logic_funct7 & 0x000007f) << 25;
	rv_instruction |= (B_rt & 0x000001f) << 20;
	rv_instruction |= (Format_rs & 0x000001f) << 15;
	rv_instruction |= (Logic_funct3 & 0x0000007) << 12;
	rv_instruction |= (C_rd & 0x000001f) << 7;
	rv_instruction |= (S_opcode & 0x000007f) << 0;

}

/**
 * r_pocedure_Arithmetic();
 */
void Engine::r_procedure_Arithmetic()
{
	if(check_add_funct(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_Sum();
	}else if(check_sub_funct(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_Sub();
	}else if(check_div(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_Div();
	}else if(check_mul(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_Mult();
	}
}

/**
 * r_procedure_ConJump();
 */
void Engine::r_procedure_ConJump()
{
	if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_SLT)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_SLT);

		// Rule [11] {ConJump.funct7 := “0000000”, ConJump.funct3 := “010”}
		ConJump_funct7 = 0x00;
		ConJump_funct3 = 0x02;
	}else if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_SLTU)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_SLTU);
		
		// Rule [12] {ConJump.funct7 := “0000000”, ConJump.funct3 := “011’”}
		ConJump_funct7 = 0x00;
		ConJump_funct3 = 0x03;
	}

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	rv_instruction = 0;	
	rv_instruction |= (ConJump_funct7 & 0x000007f) << 25;
	rv_instruction |= (B_rt & 0x000001f) << 20;
	rv_instruction |= (Format_rs & 0x000001f) << 15;
	rv_instruction |= (ConJump_funct3 & 0x0000007) << 12;
	rv_instruction |= (C_rd & 0x000001f) << 7;
	rv_instruction |= (S_opcode & 0x000007f) << 0;
}

/**
 * r_procedure_Shift(); 
 */
void Engine::r_procedure_Shift()
{
	if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_SLL)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_SLL);

		// Rule [13] {Shift.funct7 := “0000000”, Shift.funct3 := “001”}
		Shift_funct7 = 0x00;
		Shift_funct3 = 0x01;
	}else if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_SRL)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_SRL);

		// Rule [14] {Shift.funct7 := “0000000”, Shift.funct3 := “101”}
		Shift_funct7 = 0x00;
		Shift_funct3 = 0x05;
	}else if(mips32_r_instruction.getInstruction().getFunct() == INST_FUNCT_SRA)
	{
		match(mips32_r_instruction.getInstruction().getFunct(),INST_FUNCT_SRA);

		// Rule [15] {Shift.funct7 := “0100000”, Shift.funct3 := “110”}
		Shift_funct7 = 0x20;
		Shift_funct3 = 0x05;
	}
	
	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	rv_instruction = 0;	
	rv_instruction |= (Shift_funct7 & 0x000007f) << 25;
	rv_instruction |= (B_rt & 0x000001f) << 20;
	rv_instruction |= (use_register & 0x000001f) << 15;
	rv_instruction |= (Shift_funct3 & 0x0000007) << 12;
	rv_instruction |= (C_rd & 0x000001f) << 7;
	rv_instruction |= (S_opcode & 0x000007f) << 0;


	// Rule [28] {rv_instructionAddi := 00000000000000000000 + (use_register) + 0010011}
	// Clean register using instruction [addi $use_register,x0,0x00]
	// [CHECK ME]
	rv_instructionAddi |= (0x00 & 0x00fffff) << 12;
	rv_instructionAddi |= (use_register & 0x000001f) << 7;
	rv_instructionAddi |= (0x13 & 0x000007f) << 0;
}

/**
 * r_pocedure_Function(); 
 */
void Engine::r_procedure_Function()
{

	if(check_addsub(mips32_r_instruction.getInstruction().getFunct()) | check_divmul(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_Arithmetic();
	}else if(check_jr_format(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_UncJump();
	}else if(check_logic(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_Logic();
	}else if(check_shift(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_Shift();
	}else if(check_conJump(mips32_r_instruction.getInstruction().getFunct()))
	{
		r_procedure_ConJump();
	}
}

/*
* First rule of grammar and Parsing tree
*/
void Engine::r_procedure_S()
{
	match(mips32_r_instruction.getInstruction().getOpcode(),0x00);

	// Rule [0] {se funct = "" entao S.opcode := "1100111" senao S.opcode := “0110011”}
	if(mips32_r_instruction.getInstruction().getFunct() == 0x08)
	{
		S_opcode = 0x67;
	}else
	{
		S_opcode = 0x33;
	}
	r_procedure_Format();
	r_procedure_Function();
}

/**
 * Translate binary code MIPS32 in RV32.
 * Opening process of translate
 */
void Engine::r_translator()
{
	if(mips32_r_instruction.getRd().getCode() != NIL && mips32_r_instruction.getRd().getCode() == registers32[12])
	{
		flag_use_t4 = true;
	}else if(mips32_r_instruction.getRd().getCode() != NIL && mips32_r_instruction.getRd().getCode() == registers32[13])
	{
		flag_use_t5 = true;
	}

	r_procedure_S();
}

/**
 * Select type of instruction.
 * Extract each word of instruction 
 * and redirects for each function corresponding
 * @param word_inst MIPS instruction of 32 bits
 */
void Engine::selectInstruction(isa32::word_t word_inst)
{
	Mips32Instruction instruction = Mips32Instruction();

	instruction.setOpcode(((word_inst >> INST_SHIFT_OPCODE) & INST_MASK_OPCODE));
	instruction.setFunct(((word_inst >> INST_SHIFT_FUNCT) & INST_MASK_FUNCT));

	if(check_main_format(instruction.getFunct()))
	{ 
		mips32_r_instruction.setRs(Mips32Register(((word_inst >> INST_SHIFT_RS) & INST_MASK_RS)));
		mips32_r_instruction.setRt(Mips32Register(((word_inst >> INST_SHIFT_RT) & INST_MASK_RT)));
		mips32_r_instruction.setRd(Mips32Register(((word_inst >> INST_SHIFT_RD) & INST_MASK_RD)));
		instruction.setShamt(((word_inst >> INST_SHIFT_SHAMT) & INST_MASK_SHAMT));
	}else if(check_jr_format(instruction.getFunct()))
	{	
		mips32_r_instruction.setRs(Mips32Register(((word_inst >> INST_SHIFT_RS) & INST_MASK_RS)));
		mips32_r_instruction.setRd(Mips32Register());
		mips32_r_instruction.setRt(Mips32Register());
		instruction.setShamt(((word_inst >> INST_SHIFT_SHAMT) & INST_MASK_SHAMT_JR));
	}else if(check_shift_format(instruction.getFunct()))
	{
		mips32_r_instruction.setRs(Mips32Register(((word_inst >> INST_SHIFT_RS) & INST_MASK_RS)));
		mips32_r_instruction.setRt(Mips32Register(((word_inst >> INST_SHIFT_RT) & INST_MASK_RT)));
		mips32_r_instruction.setRd(Mips32Register(((word_inst >> INST_SHIFT_RD) & INST_MASK_RD)));
		mips32_r_instruction.setSa(Mips32Register(((word_inst >> INST_SHIFT_SA) & INST_MASK_SA)));
		register_management();
	}else if(check_divmul_format(instruction.getFunct()))
	{
		mips32_r_instruction.setRs(Mips32Register(((word_inst >> INST_SHIFT_RS) & INST_MASK_RS)));
		mips32_r_instruction.setRt(Mips32Register(((word_inst >> INST_SHIFT_RT) & INST_MASK_RT)));
		mips32_r_instruction.setRd(Mips32Register());
		instruction.setShamt(((word_inst >> INST_SHIFT_SHAMT) & INST_MASK_SHAMT));
		register_management();
	}

	mips32_r_instruction.setInstruction(instruction);
	r_translator();
}

/**
 * Make the management of the special 
 * registers in MIPS32 $t4 and $t5 
 */
void Engine::register_management()
{
	if(flag_use_t4 && flag_use_t5)
	{
		flag_use_t4_t5 = true;
		use_register = registers32[13];
	
		// [FIX ME]
		/**
		 * MIPS32:[sub $sp,$sp,4]   - RV32:[addi x2,x2,-4]
		 * MIPS32:[sw $t5,0($sp)]   - RV32:[sw x30,0(x2)]
		*/
		instructions_set[0] = 0xffce8e93;
		instructions_set[1] = 0xdea023;

		/**
 		 * MIPS32:[lw $t5,0($sp)]   - RV32:[lw $x30,0(x2)]
		 * MIPS32:[sw $zero,0($sp)] - RV32:[sw $zero,0(x2)]
		 * MIPS32:[addi $sp,$sp,4]  - RV32:[addi x2,x2,4]
		*/
		instructions_set[2] = 0xea683;
		instructions_set[4] = 0xea023;
		instructions_set[5] = 0xe8e93;
	}else if(flag_use_t5)
	{
		use_register = registers32[12];
	}else
	{
		use_register = registers32[13];
	}
}

/*
 * Make merge in the instructions to a instructions buffer. 
 */
isa32::word_t *Engine::getBuffer()
{	
	isa32::word_t *buffer = NULL;

	if(check_shift(mips32_r_instruction.getInstruction().getFunct()))
	{
		switch (flag_use_t4_t5)
		{
			case true:
				buffer = (isa32::word_t *)malloc(9*sizeof(isa32::word_t));
			
			// [CHECK ME]
			//	buffer[0] = instructions_set[0]; 
			//	buffer[1] = instructions_set[1];
			//	buffer[2] = rv_instructionAdd;
				buffer[0] = rv_instruction;
			//	buffer[4] = rv_instructionAddi;
			//	buffer[5] = instructions_set[2];
			//	buffer[6] = instructions_set[4];
			//	buffer[7] = instructions_set[5];
				buffer[1] = RV32_NOP;
			break;

			default:
				buffer = (isa32::word_t *)malloc(4*sizeof(isa32::word_t));

				//buffer[0] = rv_instructionAdd;
				buffer[0] = rv_instruction;
				buffer[2] = rv_instructionAddi;
				buffer[3] = RV32_NOP;
			break;
		}	
	}else if(check_divmul(mips32_r_instruction.getInstruction().getFunct()))
	{
	

		switch (flag_use_t4_t5)
		{
			case true:
				buffer = (isa32::word_t *)malloc(8*sizeof(isa32::word_t));

				// [CHECK ME]
			//	buffer[0] = instructions_set; 
			//	buffer[1] = instructions_set[1];
				buffer[0] = rv_instruction;
			//	buffer[1] = rv_instructionAddi;
			//	buffer[4] = instructions_set[2];
			//	buffer[5] = instructions_set[4];
			//	buffer[6] = instructions_set[5];
				buffer[1] = RV32_NOP;
				break;

			default:
				buffer = (isa32::word_t *)malloc(3*sizeof(isa32::word_t));
				
				buffer[0] = rv_instruction;
				buffer[1] = rv_instructionAddi;
				buffer[2] = RV32_NOP;
				break;
		}
	}else
	{
		buffer = (isa32::word_t *)malloc(2*sizeof(isa32::word_t));

		buffer[0] = rv_instruction;
		buffer[1] = RV32_NOP;
	}

	return buffer;
}

/**	
 * The engine_run() function translates a binary code into another.
 */
isa32::word_t Engine::engine_run(uint32_t instruction)
{
	selectInstruction(instruction);

	isa32::word_t *buffer = getBuffer();

	return buffer[0];
}
