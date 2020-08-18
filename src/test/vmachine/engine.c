#include "../test.h"
#include <stdio.h>
#include "utils.h"
#include <stdint.h>

extern void mips32_add(unsigned const char* mips32);
extern void mips32_addu(unsigned const char* mips32);
extern void mips32_sub(unsigned const char* mips32);
extern void mips32_subu(unsigned const char* mips32);
extern void mips32_div(unsigned const char* mips32);
extern void mips32_divu(unsigned const char* mips32);

void mips32_add_test(uint32_t mips32){
    //add $s0, $s1 $s2
    char* add = "00000010001100101000000000100000";
    
}


void mips32_addu_test(uint32_t mips32){
    //addu $s0, $s1 $s2
     char* addu = "00000010001100101000000000100001";
}

void mips32_sub_test(uint32_t mips32){
    // sub $s0, $s1 $s2
     char* sub = "00000010001100101000000000100010";
}

void mips32_subu_test(uint32_t mips32){
    // subu $s0, $s1 $s2
     char* subu = "00000010001100101000000000100011";
}

void mips32_div_test(uint32_t mips32){
    // div $s0, $s1
     char* div = "00000010000100010000000000011010";
}

void mips32_divu_test(uint32_t mips32){
    // divu $s0, $s1
     char* divu = "00000010000100010000000000011011";
}