/*
 * test_char_buffer.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"

#include "base_io/CharBuffer.h"
#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(CharBufferTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(CharBufferTestGroup, test01){
	CharBuffer* buff = new CharBuffer();
	delete buff;
}



