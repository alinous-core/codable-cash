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

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"


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
	CdbTable* table = new CdbTable(0);
	table->setName(new UnicodeString(L"test_table"));
	table->addColumn(0, L"id", CdbTableColumn::COLUMN_TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", CdbTableColumn::COLUMN_TYPE_INT, 0, true, true, L"");
	log.setTable(table);

	int size = log.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	log.toBinary(buff);

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestLogBinaryGroup, createtable_error){
	CreateTableLog log;
	CdbTable* table = new CdbTable(0);
	table->addColumn(0, L"id", CdbTableColumn::COLUMN_TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", CdbTableColumn::COLUMN_TYPE_INT, 0, true, true, L"");
	log.setTable(table);

	CdbException* ex = nullptr;
	try{
		int size = log.binarySize();
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

