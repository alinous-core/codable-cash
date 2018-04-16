/*
 * test_charsets2.cpp
 *
 *  Created on: 2018/04/16
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"

#include "charsets/CharsetManager.h"
#include "charsets/CharsetDecoder.h"
#include "charsets/CharsetEncoder.h"

#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"
#include "base_io/CharBuffer.h"

#include <stdio.h>

using namespace alinous;


TEST_GROUP(CharsetTestGroup2) {
	TEST_SETUP() {
		CharsetManager* mgr = CharsetManager::getInstance();
		UnicodeString charset(L"utf-8");
		CharsetConverter* cnv = mgr->getConverter(&charset);
		dec = cnv->newDecoder();
	}
	TEST_TEARDOWN() {
		CharsetManager::closeInstance();
	}

	CharsetDecoder* dec;
};

TEST(CharsetTestGroup2, decodeMalform5){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(16);

	bin->put(-32)->put((char)0x80)->put((char)0x80)->put((char)0x80)->put((char)0x80);
	bin->limit(bin->position());
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);

	delete bin;
	delete cout;
}

TEST(CharsetTestGroup2, decodeUnderFlow){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(1);

	bin->put(-10)->put((uint8_t)'b');
	bin->limit(2);
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);
	CHECK(result.isUnderflow());

	delete bin;
	delete cout;
}

TEST(CharsetTestGroup2, decodeMalform){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(1);

	bin->put(-1)->put((uint8_t)'b');
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);
	CHECK(result.isMalformed());

	delete bin;
	delete cout;
}

TEST(CharsetTestGroup2, decodeMalform2){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(1);

	bin->put(-10)->put((uint8_t)'b');
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);
	CHECK(result.isMalformed());

	delete bin;
	delete cout;
}

TEST(CharsetTestGroup2, decodeMalform3){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(1);

	bin->put(-10)->put((uint8_t)'b')->put((uint8_t)'b')->put((uint8_t)'b')->put((uint8_t)'b')->put((uint8_t)'b');
	bin->limit(6);
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);
	CHECK(result.isMalformed());

	delete bin;
	delete cout;
}

TEST(CharsetTestGroup2, decodeMalform4){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(16);

	bin->put(-10)->put((char)0x80)->put((char)0x80)->put((char)0x80)->put((char)0x80)->put((char)0x80);
	bin->limit(6);
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);
	CHECK(result.isMalformed());

	delete bin;
	delete cout;
}

TEST(CharsetTestGroup2, decodeOverFlow){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(1);

	bin->put((uint8_t)'a');
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);
	CHECK(result.isOverflow());

	delete bin;
	delete cout;
}

TEST(CharsetTestGroup2, decodeOverFlow2){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(1);

	bin->put((uint8_t)'a')->put((uint8_t)'b');
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);
	CHECK(result.isOverflow());

	delete bin;
	delete cout;
}

TEST(CharsetTestGroup2, decodeOverFlow3){
	ByteBuffer* bin = ByteBuffer::allocate(32);
	CharBuffer* cout = CharBuffer::allocate(1);

	bin->put(-10)->put((char)0x80)->put((char)0x80)->put((char)0x80)->put((char)0x80)->put((char)0x80);
	bin->limit(6);
	bin->position(0);

	CoderResult result = dec->decodeLoop(bin, cout);
	CHECK(result.isOverflow());

	delete bin;
	delete cout;
}

