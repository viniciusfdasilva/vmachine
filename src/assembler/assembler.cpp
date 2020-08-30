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
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// Ours
#include <assembler.h>

// Assembles a source file.
void Assembler::assembly(std::istream &input)
{
	std::string line;

	// Read all lines.
	while (std::getline(input, line))
	{
		const char *token;
		std::vector<const char *> tokens;
		char *line2 = strdup(line.c_str());

		// Parse line.
		if ((token = std::strtok(line2, delim)) != NULL)
		{
			do
				tokens.push_back(token);
			while ((token = std::strtok(NULL, delim)) != NULL);

			encode_instruction(tokens);
		}

		free(line2);
	}
}

// Assembles a source file.
isa32::word_t Assembler::assembly(std::string &line)
{
	isa32::word_t inst;
	const char *token;
	std::vector<const char *> tokens;
	char *line2 = strdup(line.c_str());

	// Parse line.
	if ((token = std::strtok(line2, delim)) != NULL)
	{
		do
			tokens.push_back(token);
		while ((token = std::strtok(NULL, delim)) != NULL);

		inst = encode_instruction(tokens);
	}

	free(line2);

	return (inst);
}