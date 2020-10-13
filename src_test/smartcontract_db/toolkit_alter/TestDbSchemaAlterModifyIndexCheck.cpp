/*
 * TestDbSchemaAlterModifyIndexCheck.cpp
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#include "TestDbSchemaAlterModifyIndexCheck.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "engine/CodableDatabase.h"

#include "trx/transaction/CdbTransaction.h"

#include "trx/transaction_log/CreateTableLog.h"
#include "trx/transaction_log/InsertLog.h"

#include "schema_table/table/CdbTable.h"

#include "schema_table/table_record/CdbTableIdentifier.h"
#include "schema_table/table_record/CdbRecord.h"

#include "schema_table/table_record_value/AbstractCdbValue.h"
#include "schema_table/table_record_value/CdbStringValue.h"
#include "schema_table/table_record_value/CdbIntValue.h"

#include "schema_table/table_record_value/VmInstanceValueConverter.h"

#include "schema_table/table_record_local/LocalCdbOid.h"
namespace codablecash {

TestDbSchemaAlterModifyIndexCheck::TestDbSchemaAlterModifyIndexCheck(TestEnv* env) : TestDbSchemaBase(env) {

}

TestDbSchemaAlterModifyIndexCheck::~TestDbSchemaAlterModifyIndexCheck() {

}

void TestDbSchemaAlterModifyIndexCheck::init(uint64_t memCapacity) {
	TestDbSchemaBase::init(memCapacity);
	createTable();
}

void TestDbSchemaAlterModifyIndexCheck::createTable() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"public");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"test_table"));

	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, false, false, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 8, false, true, L"");
	table->addColumn(0, L"email_id", AbstractCdbValue::TYPE_INT, 0, false, false, L"0");
	table->addColumn(0, L"comment", AbstractCdbValue::TYPE_STRING, 0, false, false, L"");

	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

void TestDbSchemaAlterModifyIndexCheck::insert01() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	insertRecord(trx, 1, L"tanaka", 11, L"test1");
	insertRecord(trx, 2, L"sato", 12, L"test2");
	insertRecord(trx, 3, L"saito", 12, L"test3");

	trx->commit();
}

void TestDbSchemaAlterModifyIndexCheck::insert02() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	insertRecord(trx, 1, L"tanaka", 11, L"test1");
	insertRecord(trx, 2, L"sato", 12, L"test2");
	insertRecord(trx, 3, L"saito", 13, L"test3");

	trx->commit();
}

void TestDbSchemaAlterModifyIndexCheck::insertRecord(CdbTransaction* trx,
		int id, const wchar_t* name, int email_id, const wchar_t* comment) {
	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	LocalCdbOid loid(this->loidSerial++);
	record->setOid(&loid);

	record->addValue(new CdbIntValue(id));

	if(name != nullptr){
		record->addValue(new CdbStringValue(name));
	}
	else{
		record->addValue(nullptr);
	}

	record->addValue(new CdbIntValue(email_id));
	record->addValue(new CdbStringValue(comment));

	log->addRecord(record);

	trx->insert(log);
}

} /* namespace codablecash */
