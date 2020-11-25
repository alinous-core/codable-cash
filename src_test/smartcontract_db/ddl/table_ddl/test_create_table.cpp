/*
 * test_create_table.cpp
 *
 *  Created on: 2020/05/13
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

#include "base_io/ByteBuffer.h"

#include "trx/transaction/CdbTransaction.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"
using namespace codablecash;


TEST_GROUP(TestCreateTableGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestCreateTableGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	db.createDatabase(dbDir);
	db.loadDatabase(dbDir);

	CdbTransaction* trx = db.newTransaction(); __STP(trx);
	CHECK(trx != nullptr);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);
	table->setName(new UnicodeString(L"test_table"));


	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_INT, 0, true, true, L"");

	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);

	trx->commit();
}

TEST(TestCreateTableGroup, noSchemeError){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	db.createDatabase(dbDir);
	db.loadDatabase(dbDir);

	CdbTransaction* trx = db.newTransaction(); __STP(trx);
	CHECK(trx != nullptr);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"test");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"test_table"));


	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_INT, 0, true, true, L"");

	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);

	CdbException* ex = nullptr;
	try{
		trx->commit();
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;

}


