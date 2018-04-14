/*
 * test_hashmap.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"

#include "base/HashMap.h"
#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(HashMapTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(HashMapTestGroup, construct){
	HashMap<UnicodeString, UnicodeString>* map = new HashMap<UnicodeString, UnicodeString>();

	delete map;
}

TEST(HashMapTestGroup, put01){
	UnicodeString strkey(L"key");
	UnicodeString str(L"Hello World");
	HashMap<UnicodeString, UnicodeString>* map = new HashMap<UnicodeString, UnicodeString>();

	UnicodeString* last = map->put(&strkey, &str);
	CHECK(last == nullptr);

	delete map;
}

TEST(HashMapTestGroup, put02){
	UnicodeString strkey(L"key");
	UnicodeString str(L"Hello World");
	UnicodeString str2(L"Hello World 2");
	HashMap<UnicodeString, UnicodeString>* map = new HashMap<UnicodeString, UnicodeString>();

	UnicodeString* last = map->put(&strkey, &str);
	CHECK(last == nullptr);

	last = map->put(&strkey, &str2);
	CHECK(last != nullptr);

	delete map;
}

TEST(HashMapTestGroup, put03){
	UnicodeString strkey(L"key");
	UnicodeString strkey2(L"key");
	UnicodeString str(L"Hello World");
	UnicodeString str2(L"Hello World 2");
	HashMap<UnicodeString, UnicodeString>* map = new HashMap<UnicodeString, UnicodeString>();

	UnicodeString* last = map->put(&strkey, &str);
	CHECK(last == nullptr);

	last = map->put(&strkey2, &str2);
	CHECK(last != nullptr);

	delete map;
}



TEST_GROUP(HashMapKeySetTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(HashMapKeySetTestGroup, construct){
	HashMapKeySet<UnicodeString, UnicodeString>* set = new HashMapKeySet<UnicodeString, UnicodeString>();

	delete set;
}

