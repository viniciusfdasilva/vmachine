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

// Theirs
#include <iostream>
#include <stdexcept>
#include <iomanip>

// Ours
#include <vmachine/memory.h>

// Creates a memory object.
Memory::Memory(unsigned size)
{
    size_ = size;
    data = new unsigned[size/sizeof(unsigned)];
}

// Destroy a memory object.
Memory::~Memory()
{
    delete[] data;
}

// Dumps the contents of the memory.
void Memory::dump(std::ostream &outfile)
{
    for (unsigned i = 0; i < size_/sizeof(unsigned); i++)
    {
        if (data[i] == 0)
            continue;

        outfile << i;
		outfile << " 0x" << std::setfill('0') << std::setw(8) << std::right;
		outfile << std::hex << data[i];
		outfile << std::endl;
    }
}

// Reads a word from the memory.
unsigned Memory::read(unsigned addr)
{
    // Invalid address.
    if (addr >= size_)
        throw std::range_error("invalid memory address");
    // TODO

    return (data[addr/sizeof(unsigned)]);
}

// Writes a word from the memory.
void Memory::write(unsigned addr, unsigned word)
{
    // Invalid address.
    if (addr >= size_)
        throw std::range_error("invalid memory address");

    data[addr/sizeof(unsigned)] = word;
}