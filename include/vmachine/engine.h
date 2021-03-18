

#ifndef VMACHINE_ENGINE_H_
#define VMACHINE_ENGINE_H_

#include <arch/r_format.h>
#include <arch/instruction.h>
#include <string>

using namespace std;

class Engine
{
    private:
        Rformat mips32_r_instruction;

        // Final Risc-v instruction
        isa32::word_t rv_instruction;

        isa32::word_t instructions_set[5];

        isa32::word_t use_register;

        isa32::word_t rv_instructionAddi;

        isa32::word_t rv_instructionAdd;

        bool flag_use_t4 = false, flag_use_t5 = false, flag_use_t4_t5 = false;
        
        // Translation atributtes
        isa32::word_t S_opcode;
        isa32::word_t Sum_funct7;
        isa32::word_t Sum_funct3;
        isa32::word_t Sub_funct7;
        isa32::word_t Sub_funct3;
        isa32::word_t Div_funct7;
        isa32::word_t Div_funct3;
        isa32::word_t Mult_funct7;
        isa32::word_t Mult_funct3;
        isa32::word_t Logic_funct7;
        isa32::word_t Logic_funct3;
        isa32::word_t ConJump_funct7;
        isa32::word_t ConJump_funct3;
        isa32::word_t Shift_funct7;
        isa32::word_t Shift_funct3;
        isa32::word_t UncJump_funct3;
        isa32::word_t Format_rs;
        isa32::word_t C_rd;
        isa32::word_t B_rt;
        isa32::word_t D_sa;


    public:

        /**
         * Check if these two parameters are equals.
         * @param tk1
         * @param tk2
         * */
        void match(isa32::word_t token1,isa32::word_t token2);

        /*
        * r_procedure_D();
        */
        void r_procedure_D();

        /*
        * r_procedure_C();
        */
        void r_procedure_C();

        /*
        * r_procedure_B();
        */
        void r_procedure_B();

        /*
        * r_procefure_Format()
        */
        void r_procedure_Format();

        /**
         * r_pocedure_Sum(); 
         */
        void r_procedure_Sum();

        /**
         * r_pocedure_Sub(); 
         */
        void r_procedure_Sub();

        /**
         * r_pocedure_Div(); 
         */
        void r_procedure_Div();

        /**
         * r_pocedure_Mult();
         */
        void r_procedure_Mult();

        /**
         * r_pocedure_Arithmetic();
         */
        void r_procedure_Arithmetic();

        /**
         * r_procedure_ConJump();
         */
        void r_procedure_ConJump();

        /**
         * r_procedure_Shift(); 
         */
        void r_procedure_Shift();

        /**
         * r_procedure_UncJump();
         */
        void r_procedure_UncJump();
        
        /**
         * r_procedure_Logic();
         */
        void r_procedure_Logic();

        /**
         * r_pocedure_Function(); 
         */
        void r_procedure_Function();

        /*
        * First rule of grammar and Parsing tree
        */
        void r_procedure_S();
        
        /**
         * Translate binary code MIPS32 in RV32.
         * Opening process of translate
         */
        void r_translator();

        /**
         * Make the management of the special 
         * registers in MIPS32 $t4 and $t5 
         */
        void register_management();

        /**
         * Select type of instruction.
         * Extract each word of instruction 
         * and redirects for each function corresponding
         * @param inst MIPS instruction of 32 bits
         */
        void selectInstruction(isa32::word_t word_inst);

        /*
         * Make merge in the instructions to a instructions buffer. 
        */
        isa32::word_t *getBuffer();

        /**
         * The engine_run() function translates a binary code into another.
         */
        isa32::word_t engine_run(uint32_t instruction);
        
};

#endif /* UTILS_H_ */