/*
 * test_create_table_reload.cpp
 *
 *  Created on: 2020/10/04
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "base_io/File.h"
#include "base_io/ByteBuffer.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "transaction/CdbTransaction.h"

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/TransactionLogFactory.h"
#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"


#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "table_record/CdbTableIdentifier.h"
#include "table_record/CdbRecord.h"

#include "table_record_value/AbstractCdbValue.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"

#include "table_record_local/LocalOidFactory.h"
#include "table_record_local/LocalCdbOid.h"

using namespace codablecash;


TEST_GROUP(TestCreateTableReloadGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

static void insertRecords(CodableDatabase* db);
void insertRecord(CdbTransaction* trx, LocalOidFactory* lfactory, int id,	const wchar_t* name);

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

		insertRecords(&db);

		db.closeDatabase();
	}

	{
		bool result = db.loadDatabase(dbDir);
		CHECK(result);


	}
}

void insertRecords(CodableDatabase* db){
	CdbTransaction* trx = db->newTransaction(); __STP(trx);

	LocalOidFactory* lfactory = db->getLocalOidFactory();

	insertRecord(trx, lfactory, 1, L"yamada");
	insertRecord(trx, lfactory, 2, L"tanaka");
	insertRecord(trx, lfactory, 3, L"sato");

	trx->commit();
}

void insertRecord(CdbTransaction* trx, LocalOidFactory* lfactory, int id,	const wchar_t* name){
	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	LocalCdbOid* loid = lfactory->createLocalOid(); __STP(loid);
	record->setOid(loid);

	record->addValue(new CdbIntValue(id));
	record->addValue(new CdbStringValue(name));

	log->addRecord(record);

	trx->insert(log);
}
