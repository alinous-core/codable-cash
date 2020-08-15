/*
 * test_index_scanner.cpp
 *
 *  Created on: 2020/08/14
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransaction.h"

#include "transaction_log/CreateTableLog.h"

#include "table/CdbTable.h"

#include "table_record_value/AbstractCdbValue.h"

using namespace codablecash;

static void initDb(CodableDatabase& db, File* dbDir);

TEST_GROUP(TestIndexScannerGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

void initDb(CodableDatabase& db, File* dbDir) {
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

TEST(TestIndexScannerGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	initDb(db, dbDir);



	// FIXME TestIndexScannerGroup
}
