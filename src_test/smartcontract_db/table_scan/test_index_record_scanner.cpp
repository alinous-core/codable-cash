/*
 * test_index_record_scanner.cpp
 *
 *  Created on: 2020/08/18
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "engine/CodableDatabase.h"

#include "base_io/File.h"

#include "transaction/CdbTransaction.h"

#include "transaction_log/CreateTableLog.h"

#include "table/CdbTable.h"

#include "transaction_log/InsertLog.h"

#include "table_record/CdbTableIdentifier.h"
#include "table_record/CdbRecord.h"

#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"

#include "table_record_key/CdbRecordKey.h"

#include "table_record_key/CdbIntKey.h"

#include "base/StackRelease.h"

#include "scan/IndexRecordScanner.h"
using namespace codablecash;


static void initDb(CodableDatabase& db, File* dbDir);
static void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, ArrayList<CdbRecord>* list);

TEST_GROUP(TestIndexRecordScannerGroup) {
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
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 0, true, false, L"");
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
	record->addValue(new CdbIntValue(id));

	record->addValue(new CdbStringValue(name));

	log->addRecord(record);

	if(list != nullptr){
		list->addElement((CdbRecord*)record->copy());
	}


	trx->insert(log);
}


TEST(TestIndexRecordScannerGroup, case01){
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
		insertRecord(trx, 4, L"iizuka", &list);
		insertRecord(trx, 5, L"sato", &list);
		insertRecord(trx, 6, L"fujita", &list);
		insertRecord(trx, 7, L"inoue", &list);

		trx->commit();
	}


	{
		ArrayList<const CdbRecord> listout;

		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		UnicodeString colName(L"id");
		CdbTableIdentifier tableId(L"public", L"test_table");

		CdbRecordKey* begin = new CdbRecordKey(); __STP(begin);
		begin->addKey(new CdbIntKey(3));
		CdbRecordKey* end = new CdbRecordKey(); __STP(end);
		end->addKey(new CdbIntKey(6));

		IndexRecordScanner* scanner = trx->getIndexRecordScanner(&tableId, &colName, begin, true, end, true); __STP(scanner);
		scanner->start();

		while(scanner->hasNext()){
			const CdbRecord* record = scanner->next();

			listout.addElement(record);
		}

		int maxLoop = listout.size();
		CHECK(maxLoop == 4);

		int offset = 2;
		for(int i = 0; i != maxLoop; ++i){
			const CdbRecord* record = listout.get(i);
			const CdbRecord* lastrecord = list.get(i + offset);

			AbstractCdbKey* lkey = record->toKey(); __STP(lkey);
			AbstractCdbKey* rkey = lastrecord->toKey(); __STP(rkey);

			int diff = lkey->compareTo(rkey);
			CHECK(diff == 0);
		}
	}
}

