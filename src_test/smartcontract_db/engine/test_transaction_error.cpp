/*
 * test_transaction_error.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/File.h"
#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransaction.h"

#include "engine/CdbException.h"

#include "DummyErrorTransactionLog.h"

using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestTransactionErrorGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestTransactionErrorGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	db.createDatabase(dbDir);
	db.loadDatabase(dbDir);

	CdbTransaction* trx = db.newTransaction(); __STP(trx);

	trx->createTable(new DummyErrorTransactionLog());

	CdbException* ex = nullptr;
	try{
		trx->commit();
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;

}
