/*
 * test_charsets.cpp
 *
 *  Created on: 2018/04/13
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


TEST_GROUP(CharsetTestGroup) {
	TEST_SETUP() {
		CharsetManager* mgr = CharsetManager::getInstance();
	}
	TEST_TEARDOWN() {
		CharsetManager::closeInstance();
	}

};


TEST(CharsetTestGroup, construct){
}

TEST(CharsetTestGroup, getConverter){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString charset2(L"utf_8");
	cnv = mgr->getConverter(&charset2);
	CHECK(cnv != nullptr);

	cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString charset3(L"testaaa");
	cnv = mgr->getConverter(&charset3);
	CHECK(cnv == nullptr);
}

TEST(CharsetTestGroup, convertUTF8_01){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	CharsetDecoder* dec = cnv->newDecoder();
	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(L"hello world", 0, 11);

	delete chin;
}



