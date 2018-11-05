/*
 * test_reverse_byte_buffer.cpp
 *
 *  Created on: 2018/11/02
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/ReverseByteBuffer.h"

#include <stdio.h>


using namespace alinous;

TEST_GROUP(ReverseByteBufferTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(ReverseByteBufferTestGroup, put){
	int cap = 128;
	ReverseByteBuffer* buff = new ReverseByteBuffer(128);
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


TEST(ReverseByteBufferTestGroup, bigendian){
	int cap = 128;
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(cap, true);

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

TEST(ReverseByteBufferTestGroup, littleendian){
	int cap = 128;
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(cap, false);

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

