/*
 * test_insert_parts.cpp
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"


#include "ext_binary/ExtClassObject.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm_trx/VmTransactionHandlerException.h"

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

#include "sc_analyze/ValidationError.h"

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransaction.h"

#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"
#include "transaction_log/TransactionLogFactory.h"
#include "transaction_log/AbstractTransactionLog.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "table_record/CdbTableIdentifier.h"
#include "table_record/CdbRecord.h"

#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"

#include "base_io/ByteBuffer.h"

#include "base/StackRelease.h"


using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestInsertPartGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

static void initDb(CodableDatabase& db, File* dbDir) {
	db.createDatabase(dbDir);
	db.loadDatabase(dbDir);

	CdbTransaction* trx = db.newTransaction(); __STP(trx);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"public");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"test_table"));

	table->addColumn(0, L"id", CdbTableColumn::COLUMN_TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", CdbTableColumn::COLUMN_TYPE_TEXT, 0, true, true, L"");
	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

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

TEST(TestInsertPartGroup, testBinary01){
	InsertLog log;

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log.setTable(tableId);

	CdbRecord* record = new CdbRecord();
	record->addValue(new CdbIntValue(1));
	record->addValue(new CdbStringValue(L"hello"));
	record->addValue(nullptr);

	log.addRecord(record);

	int size = log.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	log.toBinary(buff);

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestInsertPartGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	initDb(db, dbDir);

}

