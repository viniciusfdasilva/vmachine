#ifndef ARCH_MIPS32REGISTER_H_
#define ARCH_MIPS32REGISTER_H_

    #include <arch.h>
    #include <cstring>
    
class Mips32Register
{
    private:
        isa32::word_t code; // Register code
        std::string name; // Register name

    public:
        Mips32Register()
        { 
            name = "";
            code = 0xffffffff;
        }

        Mips32Register(isa32::word_t _code){setCode(_code);}
        
        void setCode(isa32::word_t _code){code = _code;}
        isa32::word_t getCode(){return code;}
        
        void setName(std::string _name){strcpy((char *)(name).c_str(),_name.c_str());}
        std::string getName(){return name;}
};

#endif // ARCH_REGISTER_H_