/*
 * TestDbSchemaAlter02.cpp
 *
 *  Created on: 2020/09/23
 *      Author: iizuka
 */

#include "TestDbSchemaAlter02.h"

#include "table/CdbTable.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "table_record_value/AbstractCdbValue.h"

#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransaction.h"

#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"

#include "table_record/CdbRecord.h"
#include "table_record/CdbTableIdentifier.h"

#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"

namespace codablecash {

TestDbSchemaAlter02::TestDbSchemaAlter02(TestEnv* env) : TestDbSchemaBase(env) {

}

TestDbSchemaAlter02::~TestDbSchemaAlter02() {

}

void TestDbSchemaAlter02::init(uint64_t memCapacity) {
	TestDbSchemaBase::init(memCapacity);
	createTable();
}

void TestDbSchemaAlter02::createTable() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"public");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"test_table"));

	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 0, true, false, L"");
	table->addColumn(0, L"email_id", AbstractCdbValue::TYPE_INT, 0, false, true, L"0");

	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

void TestDbSchemaAlter02::insert01() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	insertRecord(trx, 1, L"tanaka", 11);

	trx->commit();
}

void TestDbSchemaAlter02::insertRecord(CdbTransaction* trx, int id,	const wchar_t* name, int email_id) {
	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	record->addValue(new CdbIntValue(id));

	record->addValue(new CdbStringValue(name));
	record->addValue(new CdbIntValue(email_id));

	log->addRecord(record);

	trx->insert(log);
}

} /* namespace codablecash */
