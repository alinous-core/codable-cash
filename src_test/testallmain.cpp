
#include "CppUTest/CommandLineTestRunner.h"
#include "debug/TestExecutor.h"

const char* prog = nullptr;

int main(int ac, char** av) {
	prog = av[0];

	MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
	return CommandLineTestRunner::RunAllTests(ac, av);

}

