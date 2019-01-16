/*
 * test_char_buffer.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base_io/CharBuffer.h"
#include "base/UnicodeString.h"


using namespace alinous;

TEST_GROUP(CharBufferTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(CharBufferTestGroup, test01){
	CharBuffer* buff = CharBuffer::allocate(8);
	buff->clear();

	CHECK(buff->hasRemaining())

	delete buff;
}

TEST(CharBufferTestGroup, put){
	CharBuffer* buff = CharBuffer::allocate(8);

	buff->put(L'A');
	buff->put(0, L'B');

	CHECK(buff->get(0) == L'B');

	delete buff;
}

TEST(CharBufferTestGroup, putString){
	CharBuffer* buff = CharBuffer::allocate(16);

	UnicodeString ustr(L"Hello");
	buff->put(&ustr);

	wchar_t dest[128];
	Mem::memset(dest, 0, 128);

	buff->get(dest, 5);

	CHECK(Mem::wcscmp(dest, ustr.towString()));

	delete buff;
}

TEST(CharBufferTestGroup, putWchar_t){
	CharBuffer* buff = CharBuffer::allocate(16);

	const wchar_t* str = L"Hello";
	buff->put(str, 6);

	wchar_t dest[128]{};
	buff->get(dest, 5);

	CHECK(Mem::wcscmp(dest, str));

	delete buff;
}

TEST(CharBufferTestGroup, getWchar_tError){
	CharBuffer* buff = CharBuffer::allocate(16);

	const wchar_t* str = L"Hello";
	buff->put(str, 6);

	wchar_t dest[128]{};

	Exception* exp{nullptr};
	try{
		buff->get(dest, 128);
	}catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr)

	delete exp;
	delete buff;
}

TEST(CharBufferTestGroup, putWchar_tError){
	CharBuffer* buff = CharBuffer::allocate(4);

	const wchar_t* str = L"Hello";

	Exception* exp{nullptr};
	try{
		buff->put(str, 6);
	}catch(Exception* e){
		exp = e;
	}
	CHECK(exp != nullptr)

	delete exp;
	delete buff;
}
