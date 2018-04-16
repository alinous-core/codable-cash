/*
 * test_exceptions.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */



#include "CppUTest/CommandLineTestRunner.h"

#include "base/exceptions.h"
#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(ExceptionsTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

template<typename T>
void testException(){


	T* ex = nullptr;
	try{
		throw new T();
	}
	catch(T* e){
		ex = e;
	}
	CHECK(ex != nullptr);
	delete ex; ex = nullptr;

	ex = nullptr;
	try{
		UnicodeString msg(L"error message");
		throw new T(&msg);
	}
	catch(T* e){
		ex = e;
	}
	CHECK(ex != nullptr);
	delete ex; ex = nullptr;

	T* excause = new T();
	try{
		throw new T(excause);
	}
	catch(T* e){
		ex = e;
	}
	CHECK(ex != nullptr);
	delete ex; ex = nullptr;

	excause = new T();
	try{
		UnicodeString msg(L"error message");
		throw new T(&msg, excause);
	}
	catch(T* e){
		ex = e;
	}
	CHECK(ex != nullptr);
	delete ex; ex = nullptr;
}

TEST(ExceptionsTestGroup, ex){
	Exception* ex = new Exception();
	delete ex;
}

TEST(ExceptionsTestGroup, test01){
	testException<NumberFormatException>();
	testException<IllegalArgumentException>();
}
