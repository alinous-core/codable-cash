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


	// FIXME create table
	trx->createTable(cmd);

	trx->commit();
}
