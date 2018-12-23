/*
 * test_reverse_byte_buffer.cpp
 *
 *  Created on: 2018/11/02
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/ReverseByteBuffer.h"
#include "base_io/exceptions.h"

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


TEST(ReverseByteBufferTestGroup, put02){
	int cap = 128;
	ReverseByteBuffer* buff = new ReverseByteBuffer(128);

	buff->putLong(12);
	int64_t val = buff->getLong(0);

	CHECK(val == 12)

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
	CHECK(buff->getInt(pos) == -123456); pos += sizeof(int32_t);
	CHECK(buff->getLong(pos) == -1234567890); pos += sizeof(int64_t);
	CHECK(buff->getFloat(pos) == flt); pos += sizeof(float);
	CHECK(buff->getDouble(pos) == dbl); pos += sizeof(double);


	pos = buff->capacity();
	buff->position(0);
	ByteBuffer* wbuff = ByteBuffer::wrapWithEndian(buff->array(), pos, true);

	pos = 0;
	CHECK(wbuff->get(pos) == 'B'); pos += sizeof(char);
	CHECK(wbuff->getChar(pos) == L'C'); pos += sizeof(short);
	CHECK(wbuff->getShort(pos) == -124); pos += sizeof(short);
	CHECK(wbuff->getInt(pos) == -123456); pos += sizeof(int32_t);
	CHECK(wbuff->getLong(pos) == -1234567890); pos += sizeof(int64_t);
	CHECK(wbuff->getFloat(pos) == flt); pos += sizeof(float);
	CHECK(wbuff->getDouble(pos) == dbl); pos += sizeof(double);

	delete buff;
	delete wbuff;
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


	pos = buff->capacity();
	buff->position(0);
	ByteBuffer* wbuff = ByteBuffer::wrapWithEndian(buff->array(), pos, false);

	pos = 0;
	CHECK(wbuff->get(pos) == 'B'); pos += sizeof(char);
	CHECK(wbuff->getChar(pos) == L'C'); pos += sizeof(short);
	CHECK(wbuff->getShort(pos) == -124); pos += sizeof(short);
	CHECK(wbuff->getInt(pos) == -123456); pos += sizeof(int32_t);
	CHECK(wbuff->getLong(pos) == -1234567890); pos += sizeof(int64_t);
	CHECK(wbuff->getFloat(pos) == flt); pos += sizeof(float);
	CHECK(wbuff->getDouble(pos) == dbl); pos += sizeof(double);

	delete buff;
	delete wbuff;
}

TEST(ReverseByteBufferTestGroup, putExceptions){
	Exception* exp = nullptr;

	ByteBuffer* buff = new ReverseByteBuffer(1);
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

TEST(ReverseByteBufferTestGroup, getExceptions){
	Exception* exp = nullptr;

	ByteBuffer* buff = new ReverseByteBuffer(1);
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




