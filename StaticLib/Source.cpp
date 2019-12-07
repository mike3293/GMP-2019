#include <cstdlib>
#include <iostream>

extern "C" {
	void printN(int a)
	{
		std::cout << a;
	}

	void printS(char* str)
	{
		std::cout << str;
	}

}