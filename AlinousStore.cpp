//============================================================================
// Name        : AlinousStore.cpp
// Author      : Tomohiro Iizuka
// Version     :
// Copyright   : MIT License
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "debug/t_macros.h"

#include "base/UnicodeString.h"
#include "base/Integer.h"
#include "base/exceptions.h"

using namespace alinous;

const char* prog = nullptr;

int main(int ac, char** av) {
	prog = av[0];

	TestExecutor::get()->execute();

	return EXIT_SUCCESS;

}
