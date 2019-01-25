/*
 * test_charsets.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

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
	ByteBuffer* bout = ByteBuffer::allocate(32);

	CoderResult result = enc->encodeLoop(chin, bout);
	CHECK(result.isUnderflow());
	CHECK(!result.isOverflow());
	CHECK(!result.isUnmappable());

	CharBuffer* chout = CharBuffer::allocate(bout->position() * 3);

	bout->limit(bout->position());
	bout->position(0);
	result = dec->decodeLoop(bout, chout);
	CHECK(result.isUnderflow());
	CHECK(!result.isOverflow());
	CHECK(!result.isUnmappable());

	delete bout;
	delete chin;
	delete chout;
}

void testPatterns(UnicodeString* str){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	if(cnv == nullptr){ throw -1;}

	CharsetDecoder* dec = cnv->newDecoder();
	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(str);
	ByteBuffer* bout = ByteBuffer::allocate(str->length() * 3);

	CoderResult result = enc->encodeLoop(chin, bout);
	if(!result.isUnderflow()){ throw -1;}
	if(result.isOverflow()){ throw -1;}
	if(result.isUnmappable()){ throw -1;}

	CharBuffer* chout = CharBuffer::allocate(bout->position() * 3);

	bout->limit(bout->position());
	bout->position(0);
	result = dec->decodeLoop(bout, chout);
	if(!result.isUnderflow()){ throw -1;}
	if(result.isOverflow()){ throw -1;}
	if(result.isUnmappable()){ throw -1;}

	int pos = chout->position();
	UnicodeString str2(L"");
	for(int i = 0; i != pos; ++i){
		str2.append(chout->get(i));
	}

	if(!str2.equals(str)){ throw -1;}

	delete bout;
	delete chin;
	delete chout;
}

TEST(CharsetTestGroup, convertUTF8_02){
	UnicodeString strJp01(L"この文章は日本語です。\t\r\n漢字を含んでいます。");
	testPatterns(&strJp01);

	UnicodeString strJp02(L"この文章はNiceな日本語Ωです。Ω");
	testPatterns(&strJp02);

	UnicodeString strJp03(L"ΩΩΩΩΩ");
	testPatterns(&strJp03);

}

void overFlowTest(UnicodeString* str, int cap){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	if(cnv == nullptr){ throw -1;}

	CharsetEncoder* enc = cnv->newEncoder();


	CharBuffer* chin = CharBuffer::wrap(str);
	ByteBuffer* bout = ByteBuffer::allocate(cap);

	chin->put(L'\0');

	CoderResult result = enc->encodeLoop(chin, bout);
	if(result.isUnderflow()){ throw -1;}
	if(!result.isOverflow()){ throw -1;}
	//CHECK(!result.isUnmappable());

	delete bout;
	delete chin;
}

TEST(CharsetTestGroup, convertUTF8_DecodeOverFlow){
	UnicodeString strJp02(L"この文章はNiceな日本語Ωです。Ω");

	overFlowTest(&strJp02, 0);
	overFlowTest(&strJp02, 10);
	overFlowTest(&strJp02, 36);
	overFlowTest(&strJp02, 37);
	overFlowTest(&strJp02, 38);
}

TEST(CharsetTestGroup, convertUTF8_DecodeOverFlow2){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"この文章はNiceな日本語Ωです。Ω");

	CharsetEncoder* enc = cnv->newEncoder();


	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(100);

	bout->position(bout->limit());

	CoderResult result = enc->encodeLoop(chin, bout);
	CHECK(!result.isUnderflow());
	CHECK(result.isOverflow());
	//CHECK(!result.isUnmappable());

	delete bout;
	delete chin;
}

TEST(CharsetTestGroup, convertUTF8_DecodeOverFlow3){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"ΩΩ");

	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(1);

	chin->limit(2);

	CoderResult result = enc->encodeLoop(chin, bout);
	CHECK(!result.isUnderflow());
	CHECK(result.isOverflow());
	//CHECK(!result.isUnmappable());

	delete bout;
	delete chin;
}

TEST(CharsetTestGroup, convertUTF8_DecodeOverFlow4){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"aaa");

	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(1);

	bout->position(1);
	bout->limit(0);

	CoderResult result = enc->encodeLoop(chin, bout);
	CHECK(!result.isUnderflow());
	CHECK(result.isOverflow());
	//CHECK(!result.isUnmappable());

	delete bout;
	delete chin;
}

TEST(CharsetTestGroup, convertUTF8_DecodeOverflow5){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"");
	strJp02.append((wchar_t)0xD800).append((wchar_t)0xDC00);

	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(2);

	CoderResult result = enc->encodeLoop(chin, bout);

	CHECK(result.isOverflow());

	delete bout;
	delete chin;
}


TEST(CharsetTestGroup, convertUTF8_DecodeOverFlow02){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"");
	strJp02.append((wchar_t)0xD800).append('A');

	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(10);

	CoderResult result = enc->encodeLoop(chin, bout);

	CHECK(result.isMalformed());

	delete bout;
	delete chin;
}

TEST(CharsetTestGroup, convertUTF8_DecodeMal01){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"");
	strJp02.append((wchar_t)0xD800).append((wchar_t)0xD800);

	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(10);

	CoderResult result = enc->encodeLoop(chin, bout);

	CHECK(result.isMalformed());

	delete bout;
	delete chin;
}

TEST(CharsetTestGroup, convertUTF8_DecodeMal02){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"");
	strJp02.append((wchar_t)0xDC00).append((wchar_t)0xD800);

	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(10);

	CoderResult result = enc->encodeLoop(chin, bout);

	CHECK(result.isMalformed());

	delete bout;
	delete chin;
}

TEST(CharsetTestGroup, convertUTF8_DecodeUnderflowSalo){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"");
	strJp02.append((wchar_t)0xD800).append((wchar_t)0xDC00).append('b');

	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(10);

	CoderResult result = enc->encodeLoop(chin, bout);

	CHECK(result.isUnderflow());

	delete bout;
	delete chin;
}

TEST(CharsetTestGroup, convertUTF8_DecodeUnderFlow){
	CharsetManager* mgr = CharsetManager::getInstance();

	UnicodeString charset(L"utf-8");
	CharsetConverter* cnv = mgr->getConverter(&charset);
	CHECK(cnv != nullptr);

	UnicodeString strJp02(L"");
	strJp02.append((wchar_t)0xD800);

	CharsetEncoder* enc = cnv->newEncoder();

	CharBuffer* chin = CharBuffer::wrap(&strJp02);
	ByteBuffer* bout = ByteBuffer::allocate(10);

	CoderResult result = enc->encodeLoop(chin, bout);

	CHECK(result.isUnderflow());
	CHECK(!result.isOverflow());
	//CHECK(!result.isUnmappable());

	delete bout;
	delete chin;
}




