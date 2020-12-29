#ifndef ARCH_MIPS32INSTRUCTION_H_
#define ARCH_MIPS32INSTRUCTION_H_

    #include <arch.h>
    #include <string>
    #include <cstring>
    
class Mips32Instruction
{
    private:
        std::string name;
        isa32::word_t opcode;
        isa32::word_t funct;
        isa32::word_t shamt;

    public:
        Mips32Instruction()
        { 
            name = "";
            opcode = -1;
            funct = -1;
            shamt = -1;
        }
        
        void setName(std::string _name){strcpy((char *)(this->name).c_str(),_name.c_str());}
        std::string getName(){return this->name;}

        void setOpcode(isa32::word_t _opcode){opcode = _opcode;}
        isa32::word_t getOpcode(){return opcode;}

        void setFunct(isa32::word_t _funct){funct = _funct;}
        isa32::word_t getFunct(){return funct;}

        void setShamt(isa32::word_t _shamt){shamt = _shamt;}
        isa32::word_t getShamt(){return shamt;}
};
#endif // ARCH_INSTRUCTION_H_