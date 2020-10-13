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

#include "trx/transaction_log/AbstractTransactionLog.h"
#include "trx/transaction_log/TransactionLogFactory.h"
#include "trx/transaction_log/CreateTableLog.h"
#include "trx/transaction_log/DropTableLog.h"

#include "base_io/ByteBuffer.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/table/TableObjectFactory.h"

#include "schema_table/table/CdbTableIndex.h"

#include "schema_table/table_record_value/AbstractCdbValue.h"

#include "lang_sql/sql_join_parts/TableIdentifier.h"
using namespace codablecash;


TEST_GROUP(TestLogBinaryGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};
static bool checkBinary(ByteBuffer* buff);

bool checkBinary(ByteBuffer* buff){
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
	buff->put(-1);
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
	CdbTable* table = new CdbTable(1);
	table->setName(new UnicodeString(L"test_table"));
	table->addColumn(2, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(3, L"name", AbstractCdbValue::TYPE_INT, 0, true, false, L"");

	table->setPrimaryKey(L"id");

	log.setTable(table);

	CdbTableColumn* colId = table->getColumn(L"id");
	CHECK(colId != nullptr);

	CdbTableIndex* idx = table->getIndexByColumnOid(colId->getOid());
	CHECK(idx->isPrimaryKey());

	colId = table->getColumn(L"name");
	idx = table->getIndexByColumnOid(colId->getOid());
	CHECK(idx == nullptr);

	int size = log.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	log.toBinary(buff);

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestLogBinaryGroup, createtable_error){
	CreateTableLog log;
	CdbTable* table = new CdbTable(1);
	//table->setName(new UnicodeString(L"table1"));

	//table->addColumn(2, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	//table->addColumn(3, L"name", AbstractCdbValue::TYPE_INT, 0, true, true, L"");
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

TEST(TestLogBinaryGroup, createtable_primarykey_error){
	CreateTableLog log;
	CdbTable* table = new CdbTable(1);
	table->setName(new UnicodeString(L"test_table"));
	table->addColumn(2, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(3, L"name", AbstractCdbValue::TYPE_INT, 0, true, true, L"");

	log.setTable(table);

	CdbException* ex = nullptr;
	try{
		table->setPrimaryKey(L"id2");
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;

}

TEST(TestLogBinaryGroup, droptable01){
	DropTableLog log;

	TableIdentifier tableId;
	tableId.setTableName(new UnicodeString(L"test_table"));
	log.setTableId(&tableId);

	int size = log.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	log.toBinary(buff);

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestLogBinaryGroup, faactory_error01){
	int size = 10;
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	buff->put(100);
	buff->position(0);

	CdbException* ex = nullptr;
	try{
		TableObjectFactory::createFromBinary(buff, 10);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestLogBinaryGroup, faactory_error02){
	int size = 10;
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	buff->put(100);
	buff->position(0);

	CdbException* ex = nullptr;
	try{
		TableObjectFactory::createFromBinary(buff, 100);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

