/*
 * test_hashmap.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"


#include "base/UnicodeString.h"
#include "base/Integer.h"

#include "base/HashMap.h"

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

	// get
	UnicodeString* str2eq = map->get(&strkey2);
	CHECK(str2eq->equals(&str2));

	delete map;
}

TEST(HashMapTestGroup, keySet){
	UnicodeString strkey(L"key");

	HashMap<UnicodeString, UnicodeString>* map = new HashMap<UnicodeString, UnicodeString>();

	for(int i = 0; i != 1000; ++i){
		UnicodeString key(L"key");
		key.append(i);

		UnicodeString* value = new UnicodeString(L"value");
		value->append(i);

		map->put(&key, value);
	}

	HashMapKeySet<UnicodeString, UnicodeString>* keyset = map->keySet();
	Iterator<UnicodeString> *it = keyset->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		UnicodeString* value = map->get(key);

		delete value;
	}

	delete it;

	delete map;
}

TEST(HashMapTestGroup, keySet02){
	UnicodeString strkey(L"key");

	HashMap<Integer, UnicodeString>* map = new HashMap<Integer, UnicodeString>();

	for(int i = 0; i != 1000; ++i){
		Integer key(i);

		UnicodeString* value = new UnicodeString(L"value");
		value->append(i);

		map->put(&key, value);
	}

	HashMapKeySet<Integer, UnicodeString>* keyset = map->keySet();
	Iterator<Integer> *it = keyset->iterator();
	while(it->hasNext()){
		const Integer* key = it->next();
		UnicodeString* value = map->get(key);

		delete value;
	}

	delete it;

	delete map;
}

TEST(HashMapTestGroup, keySetWithNull){
	UnicodeString strkey(L"key");

	HashMap<Integer, UnicodeString>* map = new HashMap<Integer, UnicodeString>();

	for(int i = 0; i != 1000; ++i){
		Integer key(i);

		UnicodeString* value = new UnicodeString(L"value");
		value->append(i);

		map->put(&key, value);
	}

	map->put(nullptr, new UnicodeString(L"value"));

	HashMapKeySet<Integer, UnicodeString>* keyset = map->keySet();
	Iterator<Integer> *it = keyset->iterator();
	while(it->hasNext()){
		const Integer* key = it->next();
		UnicodeString* value = map->get(key);

		if(value == nullptr){
			continue;
		}

		delete value;
	}

	const Integer* ended = it->next();

	// remove don't work
	it->remove();

	delete it;

	delete map;
}

TEST(HashMapTestGroup, keySetWithNull02){
	HashMap<Integer, UnicodeString>* map = new HashMap<Integer, UnicodeString>();

	map->put(nullptr, new UnicodeString(L"value"));

	UnicodeString* last = map->put(nullptr, nullptr);
	delete last;

	map->clear();

	delete map;
}

TEST(HashMapTestGroup, remove01){
	HashMap<Integer, UnicodeString>* map = new HashMap<Integer, UnicodeString>();
	UnicodeString* str =  new UnicodeString(L"value");
	Integer* key = new Integer(10);
	Integer* keyx = new Integer(11);



	map->put(key, str);
	map->remove(keyx);
	map->remove(key);

	map->remove(nullptr);

	delete key;
	delete keyx;
	delete str;
	delete map;

}

TEST(HashMapTestGroup, remove02){
	HashMap<Integer, UnicodeString>* map = new HashMap<Integer, UnicodeString>();

	UnicodeString* str =  new UnicodeString(L"value");
	map->put(nullptr, str);
	map->remove(nullptr);

	delete str;
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

