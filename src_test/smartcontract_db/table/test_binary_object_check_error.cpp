/*
 * test_binary_object_check_error.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/File.h"
#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"

#include "trx/transaction/CdbTransaction.h"

#include "engine/CdbException.h"
#include "engine/CdbBinaryObject.h"

using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestBinaryObjectCheckErrorGroup) {
	TEST_SETUP() {
	}
	TEST_TEARDOWN() {
	}
};

class DummyObject : public CdbBinaryObject {
public:
	void testCheckNull(){
		CdbBinaryObject* object = nullptr;
		checkNotNull(object);
	}

	void testCheckNull2(){
		TableIdentifier* object = nullptr;
		checkNotNull(object);
	}
};

TEST(TestBinaryObjectCheckErrorGroup, case01){
	DummyObject obj;

	CdbException* ex = nullptr;
	try{
		obj.testCheckNull();
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestBinaryObjectCheckErrorGroup, case02){
	DummyObject obj;

	CdbException* ex = nullptr;
	try{
		obj.testCheckNull2();
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}
