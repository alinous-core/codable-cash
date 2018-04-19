
#include "CppUTest/CommandLineTestRunner.h"

const char* prog = nullptr;

int main(int ac, char** av) {
	prog = av[0];

	return CommandLineTestRunner::RunAllTests(ac, av);

}

