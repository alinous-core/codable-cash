/*
 * test_insert_parts_types.cpp
 *
 *  Created on: 2020/08/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base_io/File.h"
#include "base/UnicodeString.h"

#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"
#include "transaction_log/TransactionLogFactory.h"
#include "transaction_log/AbstractTransactionLog.h"

#include "transaction/CdbTransaction.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "engine/CodableDatabase.h"

#include "table_record_value/AbstractCdbValue.h"

#include "table_record/CdbTableIdentifier.h"
#include "table_record/CdbRecord.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"
#include "table_record_value/CdbByteValue.h"
#include "table_record_value/CdbShortValue.h"
#include "table_record_value/CdbLongValue.h"

#include "table_record/CdbKeyFactory.h"
using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestInsertPartTypesGroup) {
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

	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 0, true, true, L"");
	table->addColumn(0, L"bvalue", AbstractCdbValue::TYPE_BYTE, 0, true, true, nullptr);
	table->addColumn(0, L"svalue", AbstractCdbValue::TYPE_SHORT, 0, true, true, nullptr);
	table->addColumn(0, L"lvalue", AbstractCdbValue::TYPE_LONG, 0, true, true, nullptr);

	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

TEST(TestInsertPartTypesGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	initDb(db, dbDir);

	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	record->addValue(new CdbIntValue(1));
	record->addValue(new CdbStringValue(L"hello"));
	record->addValue(new CdbByteValue(2));
	record->addValue(new CdbShortValue(3));
	record->addValue(new CdbLongValue(4));

	log->addRecord(record);

	CdbTransaction* trx = db.newTransaction(); __STP(trx);
	trx->insert(log);
	trx->commit();
}

TEST(TestInsertPartTypesGroup, factory01){
	CdbKeyFactory factory;

	AbstractBtreeKey* key = factory.fromBinary(0, nullptr);
	CHECK(key == nullptr);
}



