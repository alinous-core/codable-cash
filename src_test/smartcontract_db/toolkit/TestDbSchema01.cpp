/*
 * TestDbSchema01.cpp
 *
 *  Created on: 2020/08/24
 *      Author: iizuka
 */

#include "TestDbSchema01.h"

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransaction.h"
#include "transaction_log/CreateTableLog.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "table/CdbTable.h"

#include "table_record/CdbRecord.h"
#include "table_record/CdbTableIdentifier.h"

#include "transaction_log/InsertLog.h"

#include "table_record_value/AbstractCdbValue.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"

namespace codablecash {

TestDbSchema01::TestDbSchema01(TestEnv* env) : TestDbSchemaBase(env) {

}

TestDbSchema01::~TestDbSchema01() {
	this->list1.deleteElements();
	this->list2.deleteElements();
}


void TestDbSchema01::init() {
	TestDbSchemaBase::init();
}

void TestDbSchema01::init(uint64_t memCapacity) {
	TestDbSchemaBase::init(memCapacity);
	createTable();
	insertData();
}

void TestDbSchema01::createTable() {
	createTestTable1();
	createTestTable2();
}

void TestDbSchema01::createTestTable1() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"public");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"test_table"));

	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 0, true, false, L"");
	table->addColumn(0, L"email_id", AbstractCdbValue::TYPE_INT, 0, true, false, nullptr);

	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

void TestDbSchema01::createTestTable2() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"public");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"emails"));

	table->addColumn(0, L"email_id", AbstractCdbValue::TYPE_INT, 0, true, false, nullptr);
	table->addColumn(0, L"email", AbstractCdbValue::TYPE_STRING, 0, true, false, L"");

	table->setPrimaryKey(L"email_id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

void TestDbSchema01::insertData() {
	insertData1();
	insertData2();
}

void TestDbSchema01::insertData1() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);
	insertRecord1(trx, 1, L"tanaka", 11, &list1);
	insertRecord1(trx, 2, L"yamada", 12, &list1);
	insertRecord1(trx, 3, L"yamamoto", 13, &list1);
	insertRecord1(trx, 4, L"iizuka", 14, &list1);
	insertRecord1(trx, 5, L"sato", 15, &list1);
	insertRecord1(trx, 6, L"fujita", 16, &list1);
	insertRecord1(trx, 7, L"inoue", 17, &list1);

	trx->commit();
}

void TestDbSchema01::insertRecord1(CdbTransaction* trx, int id,	const wchar_t* name, int email_id, ArrayList<CdbRecord>* list) {
	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	record->addValue(new CdbIntValue(id));

	record->addValue(new CdbStringValue(name));
	record->addValue(new CdbIntValue(email_id));

	log->addRecord(record);

	if(list != nullptr){
		list->addElement((CdbRecord*)record->copy());
	}

	trx->insert(log);
}

void TestDbSchema01::insertData2() {
	CdbTransaction* trx = getDatabase()->newTransaction(); __STP(trx);

}

} /* namespace codablecash */
