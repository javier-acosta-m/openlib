#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"
int main(int ac, char** av)
{
	std::cout << "Running ALL Tests" << std::endl;
	return CommandLineTestRunner::RunAllTests(ac, av);
}
