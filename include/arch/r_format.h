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

    Rformat() {}

    void setInstruction(Mips32Instruction inst)
    {
        instruction.setFunct(inst.getFunct());
        instruction.setName(inst.getName());
        instruction.setOpcode(inst.getOpcode());
        instruction.setShamt(inst.getShamt());
    }

    Mips32Instruction getInstruction() { return instruction; }

    void setSa(Mips32Register _sa) { sa.setCode(_sa.getCode()); }
    Mips32Register getSa() { return sa; }

    void setRd(Mips32Register _rd) { rd.setCode(_rd.getCode()); }
    Mips32Register getRd() { return rd; }

    void setRt(Mips32Register _rt) { rt.setCode(_rt.getCode()); }
    Mips32Register getRt() { return rt; }

    void setRs(Mips32Register _rs) { rs.setCode(_rs.getCode()); }
    Mips32Register getRs() { return rs; }
};

#endif