/*
 * test_base58.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "bc_base/Base58.h"
#include "base_io/ByteBuffer.h"
#include "osenv/memory.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestBase58Group) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestBase58Group, encode){
	const char* buff = "Hello World";
	int binsize = 11;

	UnicodeString* str = Base58::encode(buff, 11);

	UnicodeString ans(L"JxF12TrwUP45BMd");
	bool res = str->equals(&ans);

	CHECK(res)

	ByteBuffer* decoded = Base58::decode(&ans);

	int pos = decoded->position();
	CHECK(pos == binsize);

	decoded->position(0);

	CHECK(Mem::memcmp(decoded->array(), buff, binsize) == 0);

	delete str;
	delete decoded;
}

TEST(TestBase58Group, encodenull){
	const char* buff = "";
	UnicodeString* str = Base58::encode(buff, 0);
	UnicodeString blank(L"");

	CHECK(str->equals(&blank));

	ByteBuffer* decoded = Base58::decode(&blank);
	CHECK(decoded == nullptr)

	UnicodeString base(L"Hello World");
	UnicodeString* mulstr = base.replace(L'o', 300);
	decoded = Base58::decode(mulstr);
	CHECK(decoded == nullptr)

	delete mulstr;
}


