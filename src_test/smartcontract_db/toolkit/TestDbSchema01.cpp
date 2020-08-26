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

#include "table_record_value/AbstractCdbValue.h"

namespace codablecash {

TestDbSchema01::TestDbSchema01(TestEnv* env) : TestDbSchemaBase(env) {

}

TestDbSchema01::~TestDbSchema01() {

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

}

} /* namespace codablecash */
