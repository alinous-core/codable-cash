/*
 * test_insert_parts.cpp
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"


#include "ext_binary/ExtClassObject.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm_trx/VmTransactionHandlerException.h"

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

#include "sc_analyze/ValidationError.h"

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransaction.h"

#include "transaction_log/CreateTableLog.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

using namespace alinous;

TEST_GROUP(TestInsertPartGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

static void initDb(CodableDatabase& db, File* dbDir) {
	db.createDatabase(dbDir);
	db.loadDatabase(dbDir);

	CdbTransaction* trx = db.newTransaction(); __STP(trx);

	CreateTableLog* cmd = new CreateTableLog();
	CdbTable* table = new CdbTable(0);

	UnicodeString* testSchema = new UnicodeString(L"public");
	table->setSchemaName(testSchema);
	table->setName(new UnicodeString(L"test_table"));

	table->addColumn(0, L"id", CdbTableColumn::COLUMN_TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", CdbTableColumn::COLUMN_TYPE_TEXT, 0, true, true, L"");
	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

TEST(TestInsertPartGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	initDb(db, dbDir);

}

