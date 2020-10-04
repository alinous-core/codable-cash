/*
 * test_create_table_reload.cpp
 *
 *  Created on: 2020/10/04
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

#include "table_record_value/AbstractCdbValue.h"
using namespace codablecash;


TEST_GROUP(TestCreateTableReloadGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestCreateTableReloadGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	{
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

		db.closeDatabase();
	}

	{
		bool result = db.loadDatabase(dbDir);
		CHECK(result);
	}
}



