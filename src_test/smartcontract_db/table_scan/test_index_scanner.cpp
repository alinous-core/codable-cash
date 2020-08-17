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
#include "table_record/CdbRecord.h"

#include "table_record_value/AbstractCdbValue.h"

#include "base/ArrayList.h"

#include "transaction_log/InsertLog.h"

#include "table_record/CdbTableIdentifier.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"

#include "scan/IndexScanner.h"

using namespace codablecash;

static void initDb(CodableDatabase& db, File* dbDir);
static void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, ArrayList<CdbRecord>* list);
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

void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, ArrayList<CdbRecord>* list) {
	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	record->addValue(new CdbIntValue(1));

	record->addValue(new CdbStringValue(name));

	log->addRecord(record);

	if(list != nullptr){
		list->addElement((CdbRecord*)record->copy());
	}


	trx->insert(log);
}

TEST(TestIndexScannerGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	initDb(db, dbDir);

	ArrayList<CdbRecord> list; list.setDeleteOnExit();
	{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);
		insertRecord(trx, 1, L"tanaka", &list);
		insertRecord(trx, 2, L"yamada", &list);
		insertRecord(trx, 3, L"yamamoto", &list);

		trx->commit();
	}

	{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		UnicodeString colName(L"id");
		CdbTableIdentifier tableId(L"public", L"test_table");

		IndexScanner* scanner = trx->getRawIndexScanner(&tableId, &colName, nullptr, false, nullptr, false); __STP(scanner);

	}

	// FIXME TestIndexScannerGroup
}
