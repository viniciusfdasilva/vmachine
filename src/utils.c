/*
 * MIT License
 *
 * Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*============================================================================*
 * error()                                                                    *
 *============================================================================*/

/**
 * @brief Prints an error message and exits.
 *
 * @param msg Error message.
 */
void error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);

	exit(EXIT_FAILURE);
}

/*============================================================================*
 * debug()                                                                    *
 *============================================================================*/

/**
 * The debug() function prints a debug message in the standard output
 * error.
 */
void debug(const char *msg)
{
#ifndef NDEBUG
	fprintf(stderr, "%s\n", msg);
#else
	((void) msg);
#endif
}

/*============================================================================*
 * itoa2()                                                                    *
 *============================================================================*/

/**
 * @brief Reverses a string.
 *
 * @param str Target string.
 * @param len Length of the target string.
 */
static void reverse(char *str, int len)
	{
	int start = 0;
	int end = len -1;
	while (start < end)
	{
		char tmp;

		tmp = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = tmp;

		start++;
		end--;
	}
}

/**
 * Converts an integer value to a null-terminated string using the
 * binary base and stores the result in the array given by @p str
 * parameter.
 */
char *itoa2(int val, char *str)
{
	int i = 0;
	int isNegative = 0;

	/* Handle 0 explicitely, otherwise empty string is printed for 0 */
	if (val == 0)
	{
		for ( ; i < 32; i++)
			str[i] = '0';
		str[i] = '\0';
		return str;
	}

	while (val != 0)
	{
		int rem = val % 2;
		str[i++] = rem + '0';
		val = val/2;
	}

	if (isNegative)
		str[i++] = '-';

	for ( ; i < 32; i++)
		str[i] = '0';

	str[i] = '\0';

	reverse(str, i);

	return str;
}

/**
 * @brief Make pow of two intergers numbers
 * @param x Base
 * @param y Power positive
 * @return Wattage value
 */
int pow2(int x,int y)
{
	int i = 0;
	int pow = 1;
	
	if(y == 0) return 1;
	else if(y > 0)
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
 * @brief Convert an string value in binary base 
 * to integer value in decimal base. 
 * @param str String value in binary base
 * @return Value in decimal.
 */
int atoi2(char *str)
{
	int dec = 0;
	int index = strlen(str);

	for(int i = 0; i < (int)strlen(str); i++)
	{
		dec += ((str[i] - '0') * pow2((double)2,(double)--index));
	}
	return dec;
}

/**
 * @brief Get substring of the a master string
 * @param str Master string
 * @param init Index
 * @param Index
 */
char* substring(const char *str,const unsigned int init,const unsigned int end)
{
	char* substring = NULL;
	
	if(init <= end && (init <= (unsigned int)strlen(str) && end <= (unsigned int)strlen(str)))
	{
		substring = (char*)malloc((end-init)+1*sizeof(unsigned char));
		for(int i = 0; init+i < (end+1); i++) substring[i] = str[init+i];
		substring[(end-init)+1] = '\0';
	}else return NULL;
	return substring;
}

/**
 * @brief Concat string set
 * @param string_set[] Set of strings
 * @param buff Master buffer
 */
void concat(char *string_set[],unsigned int length,char* buff)
{
	int k = 0;

	for(int i = 0; i < (int)length; i++)
	{
		for(int j = 0; j < (int)strlen(string_set[i]); j++)
		{
			buff[k++] = string_set[i][j];
		}
	}
}

/**
 * @brief Check if two string are equals
 * @param str1
 * @param str2
 */
bool equals(const char* str1,const char* str2)
{
	return strcmp(str1,str2) == 0 ? true : false;
}

/*============================================================================*
 * __checkfail()                                                              *
 *============================================================================*/

/**
 * The __checkfail() asserts a condition.
 */
void __checkfail(int x, const char *msg, const char *filename, int linenum)
{
	if (!x)
	{
		fprintf(stderr, "%s: %s %d\n", msg, filename, linenum);
		exit(EXIT_FAILURE);
	}
}

/*============================================================================*
 * smalloc()                                                                  *
 *============================================================================*/

/**
 * The smalloc() function stands for a safe wrapper for malloc().
 */
void *smalloc(size_t n)
{
	void *ptr;

	if ((ptr = malloc(n)) == NULL)
		error("cannot allocate memory");

	return (ptr);
}
