#include <cstdlib>
#include <iostream>

extern "C" {
	void printN(unsigned short a)
	{
		std::cout << a;
	}

	void printS(char* str)
	{
		std::cout << str;
	}

	unsigned short raiseTo(int num, int exponent)
	{
		unsigned short accum = 1;
		for (int i = 0; i < exponent; i++)
		{
			accum *= num;
		}
		return accum;
	}

	// TODO compare()
}