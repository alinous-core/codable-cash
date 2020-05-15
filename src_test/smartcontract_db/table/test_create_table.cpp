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

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/TransactionLogFactory.h"
#include "transaction_log/CreateTableLog.h"

#include "base_io/ByteBuffer.h"

#include "transaction/CdbTransaction.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

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

	table->addColumn(0, L"id", CdbTableColumn::COLUMN_TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", CdbTableColumn::COLUMN_TYPE_INT, 0, true, true, L"");

	cmd->setTable(table);

	trx->createTable(cmd);

	trx->commit();
}
