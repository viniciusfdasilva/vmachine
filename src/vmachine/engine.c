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

/*
 * Free Context Grammar of R types MIPS' 32 bits instructions
 * 
 *  G:
 *	S → “000000 [opcode]” [0] Format Function
 *	Function → Arithmetic | UncJump | Logic | ConJump | Shift
 *	Arithmetic → Sum[16] | Sub[17] | Mult[18] | Div[19]
 *	Sum → “100000 [add]”[1][24] | “100001 [addu]”[1][24]
 *	Sub→ “100010 [sub]”[4][24] | “100011 [subu]”[4][24]
 *	Div → “011010 [div]”[5][20][24] | “011011 [divu]”[6][20][24]
 *	Mult → “011000 [mult]”[7][20][24] | “011001 [multu]”[7][20][24]
 *	UncJump → “001000 [jr]”
 *	Logic → “100100 [and]”[8][24] | “100111 [nor]”[9][24] | “100101 [or]”[10][24]
 *	ConJump → “101010 [slt]”[11][24] | “101001 [sltu]”[12][24]
 *	Shift → “000000 [sll]”[13][24] | “000010 [srl]”[14][24]| “000011 [sra]”[15][24]
 *	Format → “[00000-11111] [(rs | 00000)]”[19] B
 *
 *	Translation scheme from MIPS32 to RV32
 *
 *	[0] {S.opcode := “0110011”}
 *	[1] {Sum.opfunct7 := “0000000”, Sum.opfunct3 := “000”}
 *	[2] {C.rs1 := rs.value}
 *	[3] {C.rs2 := rt.value}
 *	[4] {Sub.opfunct7 := “0100000”, Sub.opfunct3 := “000”}
 *	[5] {Div.opfunct7 := “0000001”, Div.opfunct3 := “100”}
 *	[6] {Div.opfunct7 := “0000001”, Div.opfunct3 := “101”}
 *	[7] {Mult.opfunct7 := “0000001”, Mult.opfunct3 := “000”}
 *	[8] {Logic.opfunct7 := “0000000”, Logic.opfunct3 := “111”}
 *	[9] {Logic.opfunct7 := “0000000”, Logic.opfunct3 := “000”}
 *	[10] {Logic.opfunct7 := “0000000”, Logic.opfunct3 := “110”}
 *	[11] {ConJump.opfunct7 := “0000000”, ConJump.opfunct3 := “010”}
 *	[12] {ConJump.opfunct7 := “0000000”, ConJump.opfunct3 := “011’”}
 *	[13] {Shift.opfunct7 := “0000000”, Shift.opfunct3 := “001”}
 *	[14] {Shift.opfunct7 := “0000000”, Shift.opfunct3 := “101”}
 *	[15] {Shift.opfunct7 := “0100000”, Shift.opfunct3 := “110”}
 *	[16] {Shift.function7 := “0100000”, Shift.opfunct3 := “110”}
 *	[15] {Shift.opfunct7 := “0100000”, Shift.opfunct3 := “110”}
 *	[18] {Shift.opfunct7 := “0100000”, Shift.opfunct3 := “110”}
 *	[19] {Format_rs := rs.lex}
 *	[20] {inst := “000000 0000000000 rd.lex 00000 010010”}
 *	[21] {C_rd := rd.lex}
 *	[22] {B_rt := rt.lex}
 *	[23] {D_sa := sa.lex}
 *	[24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
 */

#include <vmachine.h>
#include <asm/mips32.h>
#include <utils.h>

R_instruction *r_inst;

#define SYNTATIC_ERROR "Syntatic Error!"

#define opcode r_inst->instruction->opcode
#define shamt r_inst->shamt
#define funct r_inst->instruction->funct
#define rd r_inst->rd->code
#define rs r_inst->rs->code
#define rt r_inst->rt->code
#define sa r_inst->sa->code

#define MIPS32_REGISTERS 32
#define MIPS32_INSTRUCTIONS 32
#define BASE 10

// R types attributes for translation
char rv_instruction[32];
char* rv_inst;

char *S_opcode;
char *Sum_funct7;
char *Sum_funct3;
char *Sub_funct7;
char *Sub_funct3;
char *Div_funct7;
char *Div_funct3;
char *Mult_funct7;
char *Mult_funct3;
char *Logic_funct7;
char *Logic_funct3;
char *ConJump_funct7;
char *ConJump_funct3;
char *Shift_funct7;
char *Shift_funct3;
char *Format_rs;
char *C_rd;
char *B_rt;
char *D_sa;

const char *registers32[MIPS32_REGISTERS] = {
	REG_ZERO_NUM_STR,
	REG_AT_NUM_STR, REG_V0_NUM_STR, REG_V1_NUM_STR, 
	REG_A0_NUM_STR, REG_A1_NUM_STR, REG_A2_NUM_STR,
	REG_A3_NUM_STR, REG_T0_NUM_STR, REG_T1_NUM_STR,
	REG_T2_NUM_STR, REG_T3_NUM_STR, REG_T4_NUM_STR,
	REG_T5_NUM_STR, REG_T6_NUM_STR, REG_T7_NUM_STR,
	REG_S0_NUM_STR, REG_S1_NUM_STR, REG_S2_NUM_STR,
	REG_S3_NUM_STR, REG_S4_NUM_STR, REG_S5_NUM_STR,
	REG_S6_NUM_STR, REG_S7_NUM_STR, REG_T8_NUM_STR,
	REG_T9_NUM_STR, REG_K0_NUM_STR, REG_K1_NUM_STR,
	REG_GP_NUM_STR, REG_SP_NUM_STR, REG_FP_NUM_STR,
	REG_RA_NUM_STR,
};

/**
 * Check if these two parameters are equals.
 * @param tk1
 * @param tk2
 * */
static void match(const char *tk1,const char *tk2)
{
	if(!equals(tk1,tk2)) printf("%s Between: %s and %s codes",SYNTATIC_ERROR,tk1,tk2);
}

/*
* r_procedure_D();
*/
static void r_procedure_D()
{
	if(equals(shamt,"00000"))
	{
		match(shamt,"00000");
	}else
	{
		match(sa,registers32[atoi2((char*)sa)]);

		// Rule [23] {D_sa := sa.lex}
		D_sa = (char*)sa;
	}
}

/*
* r_procedure_C();
*/
static void r_procedure_C()
{
	if(equals(shamt,"0000000000"))
	{
		match(shamt,"0000000000");
	}else
	{
		match(rd,registers32[atoi2((char*)rd)]);

		// Rule [21] {C_rd := rd.lex}
		C_rd = (char*)rd;

		r_procedure_D();
	}
}

/*
* r_procedure_B();
*/
static void r_procedure_B()
{
	if(equals(shamt,"000000000000000"))
	{
		match(shamt,"000000000000000");
	}else
	{
		match(rt,registers32[atoi2((char*)rt)]);

		// Rule [22] {B_rt := rt.lex}
		B_rt = (char*)rt;

		r_procedure_C();
	}
}

/*
* r_procefure_Format()
*/
static void r_procedure_Format()
{
	match(rs,registers32[atoi2((char*)rs)]);

	// Rule [19] {Format_rs := rs.lex} 
	Format_rs = (char*) rs;

	r_procedure_B();
}

/**
 * r_pocedure_Sum(); 
 */
static void r_procedure_Sum()
{
	if(equals(funct,INST_ADD_FUNCT_STR))
	{
		match(funct,INST_ADD_FUNCT_STR);
		
		// [1] {Sum.funct7 := “0000000”, Sum.funct3 := “000”}
		Sum_funct7 = "0000000";
		Sum_funct3 = "000";

	}else
	{
		match(funct,INST_ADDU_FUNCT_STR);

		// Rule [1] {Sum.funct7 := “0000000”, Sum.funct3 := “000”}
		Sum_funct7 = "0000000";
		Sum_funct3 = "000";

	}

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}	
	char *string_set[5];
	string_set[0] = Logic_funct7;
	string_set[1] = B_rt;
	string_set[2] = Format_rs;
	string_set[3] = Logic_funct3;
	string_set[4] = S_opcode;
	concat(string_set,5,rv_instruction);
}

/**
 * r_pocedure_Sub(); 
 */
static void r_procedure_Sub()
{
	if(equals(funct,INST_SUB_FUNCT_STR))
	{
		match(funct,INST_SUB_FUNCT_STR);

		// Rule [4] {Sub.funct7 := “”, Sub.funct3 := “000”}
		Sub_funct7 = "0100000";
		Sub_funct3 = "000";
	}else
	{
		match(funct,INST_SUBU_FUNCT_STR);

		// Rule [4] {Sub.funct7 := “”, Sub.funct3 := “000”}
		Sub_funct7 = "0100000";
		Sub_funct3 = "000";

	}

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	char *string_set[5];
	string_set[0] = Logic_funct7;
	string_set[1] = B_rt;
	string_set[2] = Format_rs;
	string_set[3] = Logic_funct3;
	string_set[4] = S_opcode;
	concat(string_set,5,rv_instruction);
}

/**
 * r_pocedure_Div(); 
 */
static void r_procedure_Div()
{
	if(equals(funct,INST_DIV_FUNCT_STR))
	{
		match(funct,INST_DIV_FUNCT_STR);

		// Rule [5] {Div.funct7 := “0000001”, Div.funct3 := “100”}
		Div_funct7 = "0000001";
		Div_funct3 = "100";
	
	}else
	{
		match(funct,INST_DIVU_FUNCT_STR);

		// Rule [6] {Div.funct7 := “0000001”, Div.funct3 := “101”}
		Div_funct7 = "0000001"; 
		Div_funct3 = "101";

	}

	// Rule [20] {inst := “000000 0000000000 rd.lex 00000 010010”}
	char* hilo_string_set[3];
	hilo_string_set[0] = "000000 0000000000";
	hilo_string_set[1] = C_rd;
	hilo_string_set[2] = "00000 010010";
	concat(hilo_string_set,3,rv_inst);
	
	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	char *string_set[5];
	string_set[0] = Div_funct7;
	string_set[1] = B_rt;
	string_set[2] = Format_rs;
	string_set[3] = Div_funct3;
	string_set[4] = S_opcode;
	concat(string_set,5,rv_instruction);
}

/**
 * r_pocedure_Mult();
 */
static void r_procedure_Mult()
{
	if(equals(funct,INST_MULT_FUNCT_STR))
	{
		match(funct,INST_MULT_FUNCT_STR);

		// Rule [7] {Mult.funct7 := “0000001”, Mult.funct3 := “000”}
		Mult_funct7 = "“0000001";
		Mult_funct3 = "000";
		
	}else
	{
		match(funct,INST_MULTU_FUNCT_STR);

		// Rule [7] {Mult.funct7 := “0000001”, Mult.funct3 := “000”}
		Mult_funct7 = "“0000001";
		Mult_funct3 = "000";
		
	}

	// Rule [20] {inst := “000000 0000000000 rd.lex 00000 010010”}
	char* hilo_string_set[3];
	hilo_string_set[0] = "000000 0000000000";
	hilo_string_set[1] = C_rd;
	hilo_string_set[2] = "00000 010010";
	concat(hilo_string_set,3,rv_inst);

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	char *string_set[5];
	string_set[0] = Mult_funct7;
	string_set[1] = B_rt;
	string_set[2] = Format_rs;
	string_set[3] = Mult_funct3;
	string_set[4] = S_opcode;
	concat(string_set,5,rv_instruction);
}

/**
 * r_pocedure_Arithmetic();
 */
static void r_procedure_Arithmetic()
{
	if(equals(funct,INST_ADD_FUNCT_STR) || equals(funct,INST_ADDU_FUNCT_STR)){
		r_procedure_Sum();
	}else if(equals(funct,INST_SUB_FUNCT_STR) || equals(funct,INST_SUBU_FUNCT_STR)){
		r_procedure_Sub();
	}else if(equals(funct,INST_DIV_FUNCT_STR) || equals(funct,INST_DIVU_FUNCT_STR)){
		r_procedure_Div();
	}else if(equals(funct,INST_MULT_FUNCT_STR) || equals(funct,INST_MULTU_FUNCT_STR)){
		r_procedure_Mult();
	}
}

/**
 * r_procedure_UncJump();
 */
static void r_procedure_UncJump()
{
	match(funct,INST_JR_FUNCT_STR);
}

/**
 * r_procedure_Logic();
 */
static void r_procedure_Logic()
{
	if(equals(funct,INST_AND_FUNCT_STR))
	{
		match(funct,INST_AND_FUNCT_STR);

		// Rule [8] {Logic.funct7 := “0000000”, Logic.funct3 := “111”}
		Logic_funct7 = "0000000"; 
		Logic_funct3 = "111";
	}else if(equals(funct,INST_NOR_FUNCT_STR))
	{
		match(funct,INST_NOR_FUNCT_STR);

		// Rule [9] {Logic.funct7 := “0000000”, Logic.funct3 := “000”}
		Logic_funct7 = "0000000";
		Logic_funct3 = "000";
	}else if(equals(funct,INST_OR_FUNCT_STR))
	{
		match(funct,INST_OR_FUNCT_STR);

		// Rule [10] {Logic.funct7 := “0000000”, Logic.funct3 := “110”}
		Logic_funct7 = "0000000";
		Logic_funct3 = "110";
	}

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	char *string_set[5];
	string_set[0] = Logic_funct7;
	string_set[1] = B_rt;
	string_set[2] = Format_rs;
	string_set[3] = Logic_funct3;
	string_set[4] = S_opcode;
	concat(string_set,5,rv_instruction);
}

/**
 * r_procedure_ConJump();
 */
static void r_procedure_ConJump()
{
	if(equals(funct,INST_SLT_FUNCT_STR))
	{
		match(funct,INST_SLT_FUNCT_STR);

		// Rule [11] {ConJump.funct7 := “0000000”, ConJump.funct3 := “010”}
		ConJump_funct7 = "0000000";
		ConJump_funct3 = "010";
	}else if(equals(funct,INST_SLTU_FUNCT_STR))
	{
		match(funct,INST_SLTU_FUNCT_STR);
		
		// Rule [12] {ConJump.funct7 := “0000000”, ConJump.funct3 := “011’”}
		ConJump_funct7 = "0000000";
		ConJump_funct3 = "011";
	}

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	char *string_set[5];
	string_set[0] = Logic_funct7;
	string_set[1] = B_rt;
	string_set[2] = Format_rs;
	string_set[3] = Logic_funct3;
	string_set[4] = S_opcode;
	concat(string_set,5,rv_instruction);
}

/**
 * r_procedure_Shift(); 
 */
static void r_procedure_Shift()
{
	if(equals(funct,INST_SLL_FUNCT_STR))
	{
		match(funct,INST_SLL_FUNCT_STR);

		// Rule [13] {Shift.funct7 := “0000000”, Shift.funct3 := “001”}
		Shift_funct7 = "0000000";
		Shift_funct3 = "001";
	}else if(equals(funct,INST_SRL_FUNCT_STR))
	{
		match(funct,INST_SRL_FUNCT_STR);

		// Rule [14] {Shift.funct7 := “0000000”, Shift.funct3 := “101”}
		Shift_funct7 = "0000000";
		Shift_funct3 = "101";
	}else if(equals(funct,INST_SRA_FUNCT_STR))
	{
		match(funct,INST_SRA_FUNCT_STR);

		// Rule [15] {Shift.funct7 := “0100000”, Shift.funct3 := “110”}
		Shift_funct7 = "0100000";
		Shift_funct3 = "110";
	}

	// Rule [24] {rv_instruction := funct7 + rs2 + rs + funct3 + rd + opcode}
	char *string_set[5];
	string_set[0] = Logic_funct7;
	string_set[1] = B_rt;
	string_set[2] = Format_rs;
	string_set[3] = Logic_funct3;
	string_set[4] = S_opcode;
	concat(string_set,5,rv_instruction);
}

/**
 * r_pocedure_Function(); 
 */
static void r_pocedure_Function()
{
	if(equals(funct,INST_ADD_FUNCT_STR) || equals(funct,INST_ADDU_FUNCT_STR) || equals(funct,INST_SUB_FUNCT_STR) || 
	   equals(funct,INST_SUBU_FUNCT_STR) || equals(funct,INST_DIV_FUNCT_STR) || equals(funct,INST_DIVU_FUNCT_STR) || 
	   equals(funct,INST_MULT_FUNCT_STR) || equals(funct,INST_MULTU_FUNCT_STR))
	{
		r_procedure_Arithmetic();
	}else if(equals(funct,INST_JR_FUNCT_STR))
	{
		r_procedure_UncJump();
	}else if(equals(funct,INST_AND_FUNCT_STR) || equals(funct,INST_NOR_FUNCT_STR) || equals(funct,INST_OR_FUNCT_STR))
	{
		r_procedure_Logic();
	}else if(equals(funct,INST_SLT_FUNCT_STR) || equals(funct,INST_SLTU_FUNCT_STR))
	{
		r_procedure_ConJump();
	}else if(equals(funct,INST_SLL_FUNCT_STR) || equals(funct,INST_SRL_FUNCT_STR) || equals(funct,INST_SRA_FUNCT_STR))
	{
		r_procedure_Shift();
	}
}

/*
 * First rule of grammar and Parsing tree
*/
static void r_procedure_S()
{
	match(opcode,R_OPCODE);

	// Rule [0] {S.opcode := “0110011”}
	S_opcode = "0110011"; 

	r_procedure_Format();
	r_pocedure_Function();
}

/**
 * Translate binary code MIPS32 in RV32.
 * Opening process of translate
 */
static void r_translator()
{
	r_procedure_S(r_inst);
}

/**
 * Select type of instruction.
 * Extract each word of instruction 
 * and redirects for each function corresponding
 * @param inst[] MIPS instruction of 32 bits
 * */
void selectInstruction(char instruction[])
{	
	char *op = substring(instruction,0,5);

	if(equals(op,R_OPCODE))
	{
		r_inst = init();
		opcode = op;
		funct = substring(instruction,26,31);
		
		int func = atoi2((char*)funct);

		if(func==INST_ADD_FUNCT || func==INST_ADDU_FUNCT || func==INST_SUB_FUNCT || func==INST_SUBU_FUNCT)
		{
			rs = substring(instruction,6,10);
			rt = substring(instruction,11,15);
			rd = substring(instruction,16,20);
			shamt = substring(instruction,21,25);
		}else if(func==INST_MULT_FUNCT || func==INST_MULTU_FUNCT || func==INST_DIV_FUNCT || func==INST_DIVU_FUNCT)
		{
			rs = substring(instruction,6,10);
			rt = substring(instruction,11,15);
			shamt = substring(instruction,16,25);
		}else if(func==INST_JR_FUNCT)
		{
			rs = substring(instruction,6,10);
			shamt = substring(instruction,11,25);
		}else if(func==INST_AND_FUNCT || func==INST_NOR_FUNCT || func==INST_OR_FUNCT)
		{
			rs = substring(instruction,6,10);
			rt = substring(instruction,11,15);
			rd = substring(instruction,16,20);
			shamt = substring(instruction,21,25);
		}else if(func==INST_SLT_FUNCT || func==INST_SLTU_FUNCT)
		{
			rs = substring(instruction,6,10);
			rt = substring(instruction,11,15);
			rd = substring(instruction,16,20);
			shamt = substring(instruction,21,25);
		}else if(func==INST_SLL_FUNCT || func==INST_SRL_FUNCT || func==INST_SRA_FUNCT)
		{
			rs = substring(instruction,6,10);
			rt = substring(instruction,11,15);
			rd = substring(instruction,16,20);
			sa = substring(instruction,21,25);
		}
		r_translator();
	}
}

/**
 * The engine_run() function translates a binary code into another.
 */
word_t engine_run(uint32_t instruction)
{
	char string_instruction[MIPS32_INSTRUCTIONS];
	itoa2(instruction,string_instruction,BASE);
	selectInstruction(string_instruction);

	return (instruction);
}
