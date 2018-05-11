
#include "test_utils/TestExecutor.h"
using namespace alinous;

const char* prog = nullptr;

int main(int ac, char** av) {
	prog = av[0];

	TestExecutor* exec = TestExecutor::get();
	return exec->execute(ac, av);
}

