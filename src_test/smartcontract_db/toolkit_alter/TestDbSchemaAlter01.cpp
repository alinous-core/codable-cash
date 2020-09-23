/*
 * TestDbSchemaAlter01.cpp
 *
 *  Created on: 2020/09/23
 *      Author: iizuka
 */

#include "TestDbSchemaAlter01.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "transaction/CdbTransaction.h"

#include "transaction_log/CreateTableLog.h"

#include "table/CdbTable.h"

#include "table_record_value/AbstractCdbValue.h"

#include "engine/CodableDatabase.h"

namespace codablecash {

TestDbSchemaAlter01::TestDbSchemaAlter01(TestEnv* env) : TestDbSchemaBase(env) {

}

TestDbSchemaAlter01::~TestDbSchemaAlter01() {

}

void TestDbSchemaAlter01::init(uint64_t memCapacity) {
	createTable();
}

void TestDbSchemaAlter01::createTable() {
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

} /* namespace codablecash */
