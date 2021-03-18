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
#include <list>

// Ours
#include <test.h>

// Import definitions.
extern std::list<test::Test *> mips32AssemblerTests(void);
extern std::list<test::Test *> vmachineTests(void);

// Top-Level test driver.
void testDriver(void)
{
	std::list<test::Test *> tests;

	tests.merge(mips32AssemblerTests());
	tests.merge(vmachineTests());

	// Run Regression tests.
	for (auto it = tests.begin(); it != tests.end(); ++it)
	{
		auto t = *it;
		bool ok = t->run();

		std::cout
			<<  ((ok) ? " passed " : " FAILED ")
			<< t->name << std::endl;
	}

	// House keeping.
	for (auto it = tests.begin(); it != tests.end(); /* noop */)
	{
		auto t = *it;
		it = tests.erase(it);
		delete t;
	}
}
