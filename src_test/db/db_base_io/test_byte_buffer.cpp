/*
 * test_byte_buffer.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base_io/ByteBuffer.h"
#include "base/UnicodeString.h"
#include "base_io/exceptions.h"

#include "base/StackRelease.h"

#include <stdio.h>


using namespace alinous;


TEST_GROUP(TestByteBufferTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(TestByteBufferTestGroup, test01){
	ByteBuffer* buff = ByteBuffer::allocate(8);
	delete buff;
}

TEST(TestByteBufferTestGroup, put){
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
	buff->putInt(pos, -123456); pos += sizeof(int32_t);
	buff->putLong(pos, -1234567890); pos += sizeof(int64_t);
	flt = -123.456;
	buff->putFloat(pos, flt); pos += sizeof(float);
	dbl = -4567.89;
	buff->putDouble(pos, dbl); pos += sizeof(double);

	pos = 0;
	CHECK(buff->get(pos) == 'B'); pos += sizeof(char);
	CHECK(buff->getChar(pos) == L'C'); pos += sizeof(short);
	CHECK(buff->getShort(pos) == -124); pos += sizeof(short);
	CHECK(buff->getInt(pos) == -123456); pos += sizeof(int32_t);
	CHECK(buff->getLong(pos) == -1234567890); pos += sizeof(int64_t);
	CHECK(buff->getFloat(pos) == flt); pos += sizeof(float);
	CHECK(buff->getDouble(pos) == dbl); pos += sizeof(double);

	delete buff;
}

TEST(TestByteBufferTestGroup, putByteBufferArray){
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

TEST(TestByteBufferTestGroup, putByteBufferArrayError01){
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

TEST(TestByteBufferTestGroup, putByteBufferArrayError02){
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

TEST(TestByteBufferTestGroup, putByteBuffer){
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

TEST(TestByteBufferTestGroup, clone){
	ByteBuffer* buff = ByteBuffer::allocate(128);
	ByteBuffer* buff2 = buff->clone();

	CHECK(buff->capacity() == buff2->capacity())

	delete buff;
	delete buff2;
}

TEST(TestByteBufferTestGroup, putExceptions){
	Exception* exp = nullptr;

	ByteBuffer* buff = ByteBuffer::allocate(1);
	buff->put(0x01);

	//////////////
	try{
		buff->put(0x02);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;	exp = nullptr;

	//////////////
	try{
		buff->put(3, 0x02);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		_ST(ByteBuffer, buff2, ByteBuffer::allocate(1));

		buff2->put(2);
		buff->put(buff2);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;	exp = nullptr;

	//////////////
	try{
		buff->putChar(L'A');
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;	exp = nullptr;

	//////////////
	try{
		buff->putChar(3, L'A');
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->putShort(1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;	exp = nullptr;

	//////////////
	try{
		buff->putShort(3, 1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->putInt(1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;	exp = nullptr;

	//////////////
	try{
		buff->putInt(3, 1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->putLong(1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;	exp = nullptr;

	//////////////
	try{
		buff->putLong(3, 1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->putFloat(1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;	exp = nullptr;

	//////////////
	try{
		buff->putFloat(3, 1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;


	//////////////
	try{
		buff->putDouble(1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp;	exp = nullptr;

	//////////////
	try{
		buff->putDouble(3, 1);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	delete buff;
}

TEST(TestByteBufferTestGroup, getExceptions){
	Exception* exp = nullptr;

	ByteBuffer* buff = ByteBuffer::allocate(1);
	buff->put(0x01);

	//////////////
	try{
		buff->get();
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->get(2);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getChar();
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getChar(2);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;


	//////////////
	try{
		buff->getShort();
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getShort(2);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getInt();
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getInt(2);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getLong();
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getLong(2);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getFloat();
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getFloat(2);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getDouble();
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	//////////////
	try{
		buff->getDouble(2);
	}
	catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr); delete exp; exp = nullptr;

	delete buff;
}
