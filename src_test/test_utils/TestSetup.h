/*
 * TestSetup.h
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#ifndef TEST_UTILS_TESTSETUP_H_
#define TEST_UTILS_TESTSETUP_H_

#include "base/UnicodeString.h"
#include "base_io/File.h"

extern const char* prog;


namespace alinous {

class File;

class TestSetup {
public:
	TestSetup();
	virtual ~TestSetup();

	void setup();
	void teardown();

	File testCaseDir();

	static void clearStatics();

	static UnicodeString TEST_SEG;
private:
	File* baseDir;
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

} /* namespace alinous */

#endif /* TEST_UTILS_TESTSETUP_H_ */
