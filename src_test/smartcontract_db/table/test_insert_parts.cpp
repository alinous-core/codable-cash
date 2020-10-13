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

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/table_record/CdbTableIdentifier.h"
#include "schema_table/table_record/CdbRecord.h"

#include "schema_table/table_record_value/CdbIntValue.h"
#include "schema_table/table_record_value/CdbStringValue.h"

#include "base_io/ByteBuffer.h"

#include "base/StackRelease.h"

#include "schema_table/table_record_value/CdbByteValue.h"
#include "schema_table/table_record_value/CdbShortValue.h"
#include "schema_table/table_record_value/CdbLongValue.h"

#include "engine/CdbException.h"

#include "transaction/CdbTransactionManager.h"

#include "schema_table/table_store/CdbStorageManager.h"

#include "schema_table/schema/Schema.h"

#include "schema_table/table_store/TableStore.h"

#include "schema_table/table_record_value/VmInstanceValueConverter.h"

#include "schema_table/table_record_local/LocalCdbOid.h"

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
	LocalCdbOid loid(1);
	record->setOid(&loid);

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

TEST(TestInsertPartGroup, testBinary02){
	InsertLog log;

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log.setTable(tableId);

	CdbRecord* record = new CdbRecord();
	record->addValue(new CdbIntValue(1));
	record->addValue(new CdbStringValue(L"hello"));
	record->addValue(new CdbByteValue(2));
	record->addValue(new CdbShortValue(3));
	record->addValue(new CdbLongValue(4));

	log.addRecord(record);

	int size = log.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	log.toBinary(buff);

	bool res = checkBinary(buff);
	CHECK(res)
}

static void initDb(CodableDatabase& db, File* dbDir) {
	db.createDatabase(dbDir);
	db.loadDatabase(dbDir);

	CdbTransaction* trx = db.newTransaction(); __STP(trx);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"public");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"test_table"));

	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 0, true, true, L"");
	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

TEST(TestInsertPartGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	initDb(db, dbDir);

	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	LocalCdbOid loid(1);
	record->setOid(&loid);

	record->addValue(new CdbIntValue(1));
	record->addValue(new CdbStringValue(L"hello"));

	log->addRecord(record);

	CdbTransaction* trx = db.newTransaction(); __STP(trx);
	trx->insert(log);
	trx->commit();
}

TEST(TestInsertPartGroup, case02_err){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	initDb(db, dbDir);

	InsertLog* log = new InsertLog();
	CdbTableIdentifier* tableId = new CdbTableIdentifier(L"wrongschema", L"test_table");
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	LocalCdbOid loid(1);
	record->setOid(&loid);

	record->addValue(new CdbIntValue(1));
	record->addValue(new CdbStringValue(L"hello"));

	log->addRecord(record);

	CdbException* ex = nullptr;
	try{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		CdbTransactionManager* mgr = trx->getTrxManager();
		mgr->commitInsert(log);
	}
	catch(CdbException* e){
		ex = e;
		delete log;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestInsertPartGroup, case03_err){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	initDb(db, dbDir);

	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	LocalCdbOid loid(1);
	record->setOid(&loid);

	record->addValue(new CdbIntValue(1));
	record->addValue(new CdbStringValue(L"hello"));
	record->addValue(new CdbStringValue(L"hello2"));

	log->addRecord(record);

	CdbException* ex = nullptr;
	try{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		CdbTransactionManager* mgr = trx->getTrxManager();
		CdbStorageManager* storeMgr = mgr->getStorageManager();

		Schema* sc = mgr->getSchema(tableId->getSchema());
		CdbTable* table = sc->getCdbTableByName(tableId->getTable());

		TableStore* store = storeMgr->getTableStore(table->getOid());
		store->validateRecord(record); // validation error
	}
	catch(CdbException* e){
		ex = e;
		delete log;
	}

	CHECK(ex != nullptr)
	delete ex;
}
