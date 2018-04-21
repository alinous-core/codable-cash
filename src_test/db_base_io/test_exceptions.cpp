/*
 * test_exceptions.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */



#include "CppUTest/CommandLineTestRunner.h"

#include "base_io/exceptions.h"
#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(BaseExceptionsTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

template<typename T>
void testException(){


	T* ex = nullptr;
	try{
		throw new T(__FILE__, __LINE__);
	}
	catch(T* e){
		ex = e;
	}
	CHECK(ex != nullptr);
	delete ex; ex = nullptr;

	ex = nullptr;
	try{
		UnicodeString msg(L"error message");
		throw new T(&msg, __FILE__, __LINE__);
	}
	catch(T* e){
		ex = e;
	}
	CHECK(ex != nullptr);
	delete ex; ex = nullptr;

	T* excause = new T(__FILE__, __LINE__);
	try{
		throw new T(excause, __FILE__, __LINE__);
	}
	catch(T* e){
		ex = e;
	}
	CHECK(ex != nullptr);
	delete ex; ex = nullptr;

	excause = new T(__FILE__, __LINE__);
	try{
		UnicodeString msg(L"error message");
		throw new T(&msg, excause, __FILE__, __LINE__);
	}
	catch(T* e){
		ex = e;
	}
	CHECK(ex != nullptr);
	delete ex; ex = nullptr;
}

TEST(BaseExceptionsTestGroup, ex){
	Exception* ex = new Exception(__FILE__, __LINE__);
	delete ex;
}

TEST(BaseExceptionsTestGroup, test01){
	testException<BufferUnderflowException>();
	testException<BufferOverflowException>();
}
