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

	UnicodeString* str = Base58::encode(buff, binsize);

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

TEST(TestBase58Group, encode01_1){
	const char* buff = "123";
	int binsize = 3;

	UnicodeString* str = Base58::encode(buff, binsize);

	ByteBuffer* decoded = Base58::decode(str);

	int pos = decoded->position();
	CHECK(pos == binsize);

	decoded->position(0);

	CHECK(Mem::memcmp(decoded->array(), buff, binsize) == 0);

	delete str;
	delete decoded;
}

TEST(TestBase58Group, encode02){
	char* buff = new char[7]{};
	int binsize = 7;

	UnicodeString* str = Base58::encode(buff, binsize);

	UnicodeString ans(L"1111111");
	bool res = str->equals(&ans);

	CHECK(res)

	ByteBuffer* decoded = Base58::decode(&ans);

	int pos = decoded->position();
	CHECK(pos == binsize);

	decoded->position(0);

	CHECK(Mem::memcmp(decoded->array(), buff, binsize) == 0);

	delete [] buff;
	delete str;
	delete decoded;
}

TEST(TestBase58Group, encode02_2){
	char* buff = new char[1]{};
	int binsize = 1;

	UnicodeString* str = Base58::encode(buff, binsize);

	UnicodeString ans(L"1");
	bool res = str->equals(&ans);

	CHECK(res)

	ByteBuffer* decoded = Base58::decode(&ans);

	int pos = decoded->position();
	CHECK(pos == binsize);

	decoded->position(0);

	CHECK(Mem::memcmp(decoded->array(), buff, binsize) == 0);

	delete [] buff;
	delete str;
	delete decoded;
}

static ByteBuffer* makeData(){
	ByteBuffer* data = ByteBuffer::allocateWithEndian(8, true);
	StackRelease<ByteBuffer> __st_data(data);
	data->putLong(3471844090L);
	data->position(0);

	ByteBuffer* result = ByteBuffer::allocateWithEndian(8, true);

	char ch = data->get();
	ch = data->get();
	ch = data->get();
	ch = data->get(); result->put(ch);
	ch = data->get(); result->put(ch);
	ch = data->get(); result->put(ch);
	ch = data->get(); result->put(ch);
	ch = data->get(); result->put(ch);

	return result;
}

TEST(TestBase58Group, encode03){
	ByteBuffer* data = makeData();
	StackRelease<ByteBuffer> __st_data(data);


	int binsize = data->position();
	data->position(0);
	char* buff = (char*)data->array();

	UnicodeString* str = Base58::encode(buff, binsize);

	UnicodeString ans(L"16Ho7Hs");
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
	delete str;
}


