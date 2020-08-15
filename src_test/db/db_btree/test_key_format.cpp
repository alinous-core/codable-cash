/*
 * test_key_format.cpp
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */


#include "btreekey/BtreeKeyFactory.h"
#include "test_utils/t_macros.h"

#include "btreekey/exceptions.h"
#include "btree/exceptions.h"


using namespace alinous;

TEST_GROUP(TestKeyFormatGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestKeyFormatGroup, exceptions){
	testException<NodeStructureException>();
	testException<KeyFormatException>();
}

TEST(TestKeyFormatGroup, noKeyType){
	Exception* ex;
	try{
		BtreeKeyFactory factory;
		factory.fromBinary(100, nullptr);
	}
	catch(Exception* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}


