/*
 * test_byte_buffer.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"

#include "base_io/ByteBuffer.h"
#include "base/UnicodeString.h"
#include "base_io/exceptions.h"

#include <stdio.h>


using namespace alinous;


TEST_GROUP(ByteBufferTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(ByteBufferTestGroup, test01){
	ByteBuffer* buff = ByteBuffer::allocate(8);
	delete buff;
}

TEST(ByteBufferTestGroup, put){
	int cap = 128;
	ByteBuffer* buff = ByteBuffer::allocate(128);
	CHECK(cap == buff->capacity());

	buff->put('A');
	buff->putChar(L'B');
	buff->putShort((short)124);
	buff->putInt(123456);
	buff->putLong(1234567890);
	float flt = 123.456;
	buff->putFloat(flt);
	double dbl = 4567.89;
	buff->putDouble(dbl);

	buff->position(0);
	CHECK(buff->get() == 'A');
	CHECK(buff->getChar() == L'B');
	CHECK(buff->getShort() == 124);
	CHECK(buff->getInt() == 123456);
	CHECK(buff->getLong() == 1234567890);
	CHECK(buff->getFloat() == flt);
	CHECK(buff->getDouble() == dbl);

	buff->position(0);
	int pos = 0;
	buff->put(pos, 'B'); pos += sizeof(char);
	buff->putChar(pos, L'C'); pos += sizeof(short);
	buff->putShort(pos, (short)-124); pos += sizeof(short);
	buff->putInt(pos, -123456); pos += sizeof(int);
	buff->putLong(pos, -1234567890); pos += sizeof(int64_t);
	flt = -123.456;
	buff->putFloat(pos, flt); pos += sizeof(float);
	dbl = -4567.89;
	buff->putDouble(pos, dbl); pos += sizeof(double);

	pos = 0;
	CHECK(buff->get(pos) == 'B'); pos += sizeof(char);
	CHECK(buff->getChar(pos) == L'C'); pos += sizeof(short);
	CHECK(buff->getShort(pos) == -124); pos += sizeof(short);
	CHECK(buff->getInt(pos) == -123456); pos += sizeof(int);
	CHECK(buff->getLong(pos) == -1234567890); pos += sizeof(int64_t);
	CHECK(buff->getFloat(pos) == flt); pos += sizeof(float);
	CHECK(buff->getDouble(pos) == dbl); pos += sizeof(double);

	delete buff;
}

TEST(ByteBufferTestGroup, putByteBufferArray){
	int cap = 128;
	ByteBuffer* buff = ByteBuffer::allocate(128);
	const char* str = "Hello Wrold";

	buff->put((const uint8_t*)str, 12);


	buff->position(0);
	char dest[12]{};
	buff->get((uint8_t*)dest, 12);

	CHECK(strcmp(dest, str) == 0);

	delete buff;
}

TEST(ByteBufferTestGroup, putByteBufferArrayError01){
	int cap = 128;
	ByteBuffer* buff = ByteBuffer::allocate(4);
	const char* str = "Hello Wrold";

	Exception* exp{nullptr};
	try{
		buff->put((const uint8_t*)str, 12);
	}catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr)

	delete exp;
	delete buff;
}

TEST(ByteBufferTestGroup, putByteBufferArrayError02){
	int cap = 128;
	ByteBuffer* buff = ByteBuffer::allocate(128);
	const char* str = "Hello Wrold";

	buff->put((const uint8_t*)str, 12);


	buff->position(0);
	char dest[12]{};


	Exception* exp{nullptr};
	try{
		buff->get((uint8_t*)dest, 200);
	}catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr)

	delete exp;
	delete buff;
}

TEST(ByteBufferTestGroup, putByteBuffer){
	int cap = 128;
	ByteBuffer* buff = ByteBuffer::allocate(128);
	ByteBuffer* buff2 = ByteBuffer::allocate(128);
	CHECK(cap == buff->capacity());

	buff->put('A');
	buff->putChar(L'B');
	buff->putShort((short)124);
	buff->putInt(123456);
	buff->putLong(1234567890);
	float flt = 123.456;
	buff->putFloat(flt);
	double dbl = 4567.89;
	buff->putDouble(dbl);

	buff2->put(buff);
	CHECK(buff2->position() == buff->limit());

	buff2->position(0);
	CHECK(buff2->get() == 'A');
	CHECK(buff2->getChar() == L'B');
	CHECK(buff2->getShort() == 124);
	CHECK(buff2->getInt() == 123456);
	CHECK(buff2->getLong() == 1234567890);
	CHECK(buff2->getFloat() == flt);
	CHECK(buff2->getDouble() == dbl);

	ByteBuffer* buff3 = ByteBuffer::wrap(buff2->array(), buff2->limit());

	CHECK(buff3->get() == 'A');
	CHECK(buff3->getChar() == L'B');
	CHECK(buff3->getShort() == 124);
	CHECK(buff3->getInt() == 123456);
	CHECK(buff3->getLong() == 1234567890);
	CHECK(buff3->getFloat() == flt);
	CHECK(buff3->getDouble() == dbl);

	delete buff;
	delete buff2;
	delete buff3;
}
