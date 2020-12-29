#ifndef ARCH_R_FORMAT_H
#define ARCH_R_FORMAT_H_

    #include <arch/instruction.h>
    #include <arch/register.h>
    
class Rformat
{
    private:
        Mips32Instruction instruction;
        Mips32Register sa;
        Mips32Register rs;
        Mips32Register rd;
        Mips32Register rt;

    public:
    
        Rformat(){ }
        
    

        void setInstruction(Mips32Instruction inst){
            instruction.setFunct(inst.getFunct());
            instruction.setName(inst.getName());
            instruction.setOpcode(inst.getOpcode());
            instruction.setShamt(inst.getShamt());
        }
        
        Mips32Instruction getInstruction(){return instruction;}

        void setSa(Mips32Register _sa){sa.setCode(_sa.getCode());}
        Mips32Register getSa(){return sa;}

        void setRd(Mips32Register _rd){rd.setCode(_rd.getCode());}
        Mips32Register getRd(){return rd;}

        void setRt(Mips32Register _rt){rt.setCode(_rt.getCode());}
        Mips32Register getRt(){return rt;}

        void setRs(Mips32Register _rs){rs.setCode(_rs.getCode());}
        Mips32Register getRs(){return rs;}        
};

#endif