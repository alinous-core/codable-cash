/*
 * test_byte_buffer.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"

#include "base_io/ByteBuffer.h"
#include "base/UnicodeString.h"

using namespace alinous;


TEST_GROUP(ByteBufferTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(ByteBufferTestGroup, test01){
	ByteBuffer* buff = ByteBuffer::allocate(8);
	delete buff;
}


