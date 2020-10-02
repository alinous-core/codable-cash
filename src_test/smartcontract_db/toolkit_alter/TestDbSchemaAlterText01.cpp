/*
 * TestDbSchemaAlterText01.cpp
 *
 *  Created on: 2020/10/02
 *      Author: iizuka
 */

#include "TestDbSchemaAlterText01.h"

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

#include "table_record_local/LocalCdbOid.h"

namespace codablecash {

TestDbSchemaAlterText01::TestDbSchemaAlterText01(TestEnv* env) : TestDbSchemaBase(env) {


}

TestDbSchemaAlterText01::~TestDbSchemaAlterText01() {

}

void TestDbSchemaAlterText01::init(uint64_t memCapacity) {
	TestDbSchemaBase::init(memCapacity);
	createTable();
}

void TestDbSchemaAlterText01::createTable() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"public");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"test_table"));

	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, false, false, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 8, false, false, L"");
	table->addColumn(0, L"email_id", AbstractCdbValue::TYPE_INT, 0, false, false, L"0");

	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

void TestDbSchemaAlterText01::insert01() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	insertRecord(trx, 1, L"tanaka", 11);
	insertRecord(trx, 2, L"sato", 12);
	insertRecord(trx, 3, nullptr, 13);

	trx->commit();
}

void TestDbSchemaAlterText01::insertRecord(CdbTransaction* trx, int id,	const wchar_t* name, int email_id) {
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

	log->addRecord(record);

	trx->insert(log);
}

} /* namespace alinous */
