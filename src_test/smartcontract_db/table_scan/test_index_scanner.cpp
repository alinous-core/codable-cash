/*
 * test_index_scanner.cpp
 *
 *  Created on: 2020/08/14
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

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

#include "table_record_key/CdbIntKey.h"

#include "table_record_key/CdbRecordKey.h"

#include "table_record_local/LocalCdbOid.h"

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
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 0, true, false, L"");
	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, ArrayList<CdbRecord>* list) {
	static int serial = 1;

	InsertLog* log = new InsertLog();

	CdbTableIdentifier* tableId = new CdbTableIdentifier();
	tableId->setTable(new UnicodeString(L"test_table"));
	log->setTable(tableId);

	CdbRecord* record = new CdbRecord();
	LocalCdbOid loid(serial++);
	record->setOid(&loid);

	record->addValue(new CdbIntValue(id));

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

		scanner->start();

		int count = 0;
		while(scanner->hasNext()){
			const CdbOid* oid = scanner->next();
			count++;
		}

		CHECK(count == 3)
	}
}

TEST(TestIndexScannerGroup, case01_err){
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

	CdbException* ex = nullptr;
	try{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		UnicodeString colName(L"id");
		CdbTableIdentifier tableId(L"public2", L"test_table");

		IndexScanner* scanner = trx->getRawIndexScanner(&tableId, &colName, nullptr, false, nullptr, false); __STP(scanner);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestIndexScannerGroup, case02_err){
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

	CdbException* ex = nullptr;
	try{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		UnicodeString colName(L"id");
		CdbTableIdentifier tableId(L"public", L"test_table2");

		IndexScanner* scanner = trx->getRawIndexScanner(&tableId, &colName, nullptr, false, nullptr, false); __STP(scanner);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestIndexScannerGroup, case03_err){
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

	CdbException* ex = nullptr;
	try{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		UnicodeString colName(L"name");
		CdbTableIdentifier tableId(L"public", L"test_table");

		IndexScanner* scanner = trx->getRawIndexScanner(&tableId, &colName, nullptr, false, nullptr, false); __STP(scanner);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestIndexScannerGroup, case04_err){
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

	CdbException* ex = nullptr;
	try{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		UnicodeString colName(L"aaaaa");
		CdbTableIdentifier tableId(L"public", L"test_table");

		IndexScanner* scanner = trx->getRawIndexScanner(&tableId, &colName, nullptr, false, nullptr, false); __STP(scanner);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestIndexScannerGroup, case05){
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
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		UnicodeString colName(L"id");
		CdbTableIdentifier tableId(L"public", L"test_table");

		CdbRecordKey* begin = new CdbRecordKey(); __STP(begin);
		begin->addKey(new CdbIntKey(3));
		CdbRecordKey* end = new CdbRecordKey(); __STP(end);
		end->addKey(new CdbIntKey(6));

		IndexScanner* scanner = trx->getRawIndexScanner(&tableId, &colName, begin, true, end, true); __STP(scanner);

		scanner->start();

		int count = 0;
		while(scanner->hasNext()){
			const CdbOid* oid = scanner->next();
			count++;
		}

		CHECK(count == 4);
	}
}

TEST(TestIndexScannerGroup, case06){
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
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		UnicodeString colName(L"id");
		CdbTableIdentifier tableId(L"public", L"test_table");

		CdbRecordKey* begin = new CdbRecordKey(); __STP(begin);
		begin->addKey(new CdbIntKey(3));
		CdbRecordKey* end = new CdbRecordKey(); __STP(end);
		end->addKey(new CdbIntKey(6));

		IndexScanner* scanner = trx->getRawIndexScanner(&tableId, &colName, begin, false, end, false); __STP(scanner);

		scanner->start();

		int count = 0;
		while(scanner->hasNext()){
			const CdbOid* oid = scanner->next();
			count++;
		}

		CHECK(count == 2);
	}
}
