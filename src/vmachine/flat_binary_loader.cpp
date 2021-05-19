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
#include <elf.h>
#include <fstream>
#include <string>
#include <stdexcept>

// Ours
#include <engine.h>
#include <vmachine.h>

using namespace vmachine;

// Starts the virtual machine.
void VMachine::load(std::string &binfile)
{
	Engine a;
	std::string line;
	std::ifstream infile(binfile);

	if (!infile.is_open())
		throw std::invalid_argument("cannot open input file");

	// Load Flat Binary file.
	for (isa32::word_t addr = startAddr; std::getline(infile, line); addr += sizeof(isa32::word_t))
	{
		isa32::word_t inst = a.assembly(line);
		memory.write(addr, inst);
	}
}
