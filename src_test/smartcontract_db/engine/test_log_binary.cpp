/*
 * test_log_binary.cpp
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/File.h"
#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"

#include "engine/CdbException.h"

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/TransactionLogFactory.h"
#include "transaction_log/CreateTableLog.h"

#include "base_io/ByteBuffer.h"


using namespace codablecash;


TEST_GROUP(TestLogBinaryGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

static bool checkBinary(ByteBuffer* buff){
	int lastSize = buff->capacity();

	buff->position(0);
	AbstractTransactionLog* element = TransactionLogFactory::createFromBinary(buff); __STP(element);

	int size = element->binarySize();
	if(lastSize != size){
		return false;
	}

	ByteBuffer* buff2 = ByteBuffer::allocateWithEndian(size, true); __STP(buff2);
	element->toBinary(buff2);

	if(buff2->position() != size){
		return false;
	}

	return Mem::memcmp(buff->array(), buff2->array(), size) == 0;
}

TEST(TestLogBinaryGroup, checkError){
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(10, true); __STP(buff);
	buff->put(100);
	buff->position(0);

	CdbException* ex = nullptr;
	try{
		TransactionLogFactory::createFromBinary(buff);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestLogBinaryGroup, createtable){
	CreateTableLog log;

	int size = log.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	log.toBinary(buff);

	bool res = checkBinary(buff);
	CHECK(res)
}


