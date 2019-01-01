/*
 * test_base58.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "bc_base/Base58.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestBase58Group) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestBase58Group, encode){
	const char* buff = "Hello World";
	UnicodeString* str = Base58::encode(buff, 11);

	UnicodeString ans(L"JxF12TrwUP45BMd");
	bool res = str->equals(&ans);

	CHECK(res)
}



