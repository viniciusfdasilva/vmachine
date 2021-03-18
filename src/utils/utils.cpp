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

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

/**
 * @brief Reverses a string.
 *
 * @param str Target string.
 * @param len Length of the target string.
 */
static std::string reverse(std::string str, int len)
{
	int start = 0;
	int end = len -1;

	while (start < end)
	{
		char tmp;

		tmp = *(str.c_str()+start);
		*((char *)str.c_str()+start) = *((char *)str.c_str()+end);
		*((char *)str.c_str()+end) = tmp;

		start++;
		end--;
	}

	return str;
}

/**
 * Converts an integer value to a null-terminated string using the
 * binary base and stores the result in the array given by @p str
 * parameter.
 */
std::string itoa2(int val)
{
	std::string str;
	int i = 0;
	int isNegative = 0;

	/* Handle 0 explicitely, otherwise empty string is printed for 0 */

	if (val == 0)
	{
		for ( ; i < 32; i++)
			str.insert(i,"0");
		return str;
	}

	while (val != 0)
	{
		int rem = val % 2;
		std::string s;
		s.push_back((rem + '0'));

		str.insert(i++,s);
		val = val/2;
	}

	if (isNegative)
		str.insert(i++,"-");

	for ( ; i < 32; i++)
		str.insert(i,"0");

	str = reverse(str,i);

	return str;
}


/**
 * @brief Make pow of two integers numbers
 *
 * @param x Base
 * @param y Power positive
 * @return Wattage value
 */
int pow2(int x,int y)
{
	int i = 0;
	int pow = 1;

	if (y == 0) return 1;
	else if (y > 0)
	{
		while(i < y)
		{
			pow *= x;
			i++;
		}
	}
	return pow;
}

/**
 * @brief Convert an string value in binary base to integer value in
 * decimal base.
 *
 * @param str String value in binary base
 * @return Value in decimal.
 */
int atoi2(std::string str)
{
	int dec = 0;
	int index = (int)str.size();

	for (int i = 0; i < (int)str.size(); i++)
		dec += ((str[i] - '0') * pow2((double)2,(double)--index));

	return dec;
}

/**
 * @brief Get substring of the a master string
 *
 * @param str Master string
 * @param init Index
 * @param Index
 */
std::string substring(std::string str,const unsigned int init,const unsigned int end)
{
	std::string substring;

	if (init <= end && (init <= (unsigned int)str.size() && end <= (unsigned int)str.size()))
	{
		int i,j;

		for (i = init,j = 0; i < (int)end+1; i++,j++){
			std::string s;

			s.push_back(str[i]);
			substring.insert(j,s);
		}
	}else return NULL;
	return substring;
}

/**
 * @brief Check if two string are equals
 *
 * @param str1
 * @param str2
 */
bool equals(std::string str1,std::string str2)
{
	return str1.compare(str2) == 0 ? true : false;
}

// Prints an error message and aborts.
void error(const std::string &msg)
{
	std::cerr << msg << std::endl;
	std::abort();
}
