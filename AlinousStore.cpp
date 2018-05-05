//============================================================================
// Name        : AlinousStore.cpp
// Author      : Tomohiro Iizuka
// Version     :
// Copyright   : MIT License
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "base/UnicodeString.h"
#include "base/Integer.h"
#include "base/exceptions.h"

using namespace alinous;

class TInteger : public Integer {
public:
	static void test_error2(UnicodeString* str, int offset, int radix, bool negative){
		int value;
		NumberFormatException* exp = nullptr;
		try{
			value = Integer::parse(str, offset, radix, negative);
		}
		catch(NumberFormatException* e){
			const char* str = "Exception\n";
			puts(str);
			exp = e;

		}
	}
};

int main() {
	const char* str = "Hello World";
	puts(str);

	//UnicodeString strerror5(L"2147483648");
	UnicodeString strerror5(L"2147483649");

	//TInteger::test_error2(&strerror5, 0, 10, true);
	TInteger::test_error2(&strerror5, 0, 10, false);


	return EXIT_SUCCESS;

}
