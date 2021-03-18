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

#ifndef ARCH_MIPS32INSTRUCTION_H_
#define ARCH_MIPS32INSTRUCTION_H_

#include <arch.h>
#include <string>
#include <cstring>

class Mips32Instruction
{
    private:

        std::string name_ = "";
        isa32::word_t opcode_ = 0;
        isa32::word_t funct_ = 0;
        isa32::word_t shamt_ = 0;

    public:
        Mips32Instruction() { }

        void setName(std::string name)
        {
            this->name_ = name;
        }

        std::string getName()
		{
			return this->name_;
		}

        void setOpcode(isa32::word_t opcode)
		{
			opcode_ = opcode;
		}

        isa32::word_t getOpcode()
		{
			return opcode_;
		}

        void setFunct(isa32::word_t funct)
		{
			funct_ = funct;
		}

        isa32::word_t getFunct()
		{
			return funct_;
		}

        void setShamt(isa32::word_t shamt)
		{
			shamt_ = shamt;
		}

        isa32::word_t getShamt()
		{
			return shamt_;
		}
};

#endif // ARCH_INSTRUCTION_H_