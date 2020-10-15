/*
 * test_scan_part.cpp
 *
 *  Created on: 2020/06/09
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"


#include "ext_binary/ExtClassObject.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/vm_trx/VmTransactionHandlerException.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "engine/sc_analyze/ValidationError.h"

#include "engine/CodableDatabase.h"

#include "trx/transaction/CdbTransaction.h"

#include "trx/transaction_log/CreateTableLog.h"
#include "trx/transaction_log/InsertLog.h"
#include "trx/transaction_log/TransactionLogFactory.h"
#include "trx/transaction_log/AbstractTransactionLog.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/record/table_record/CdbTableIdentifier.h"
#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/record/table_record_value/CdbIntValue.h"
#include "schema_table/record/table_record_value/CdbStringValue.h"

#include "base_io/ByteBuffer.h"

#include "base/StackRelease.h"

#include "trx/scan/transaction_scanner/TableTransactionScanner.h"

#include "schema_table/record/table_record_key/AbstractCdbKey.h"

#include "scan_select/scan_condition/base/RootScanCondition.h"

#include "schema_table/record/table_record_value/VmInstanceValueConverter.h"

#include "schema_table/record/table_record_local/LocalCdbOid.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestScanPartGroup) {
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

	table->addColumn(0, L"id", AbstractCdbValue::TYPE_INT, 0, true, true, nullptr);
	table->addColumn(0, L"name", AbstractCdbValue::TYPE_STRING, 0, true, true, L"");
	table->setPrimaryKey(L"id");

	cmd->setTable(table);

	trx->createTable(cmd);
	trx->commit();
}

static void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, ArrayList<CdbRecord>* list) {
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

static bool listequals(ArrayList<CdbRecord>& list, ArrayList<CdbRecord>& listout){
	int maxLoop = list.size();

	if(maxLoop != listout.size()){
		return false;
	}

	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* lRecord = list.get(i);
		CdbRecord* rRecord = listout.get(i);

		AbstractCdbKey* lkey = lRecord->toKey(); __STP(lkey);
		AbstractCdbKey* rkey = rRecord->toKey(); __STP(rkey);

		int result = lkey->compareTo(rkey);
		if(result != 0){
			return false;
		}
	}

	return true;
}

TEST(TestScanPartGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	ArrayList<CdbRecord> list; list.setDeleteOnExit();
	ArrayList<CdbRecord> listout; listout.setDeleteOnExit();

	initDb(db, dbDir);

	{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);
		insertRecord(trx, 1, L"tanaka", &list);
		insertRecord(trx, 2, L"yamada", &list);
		insertRecord(trx, 3, L"yamamoto", &list);

		trx->commit();
	}


	{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		CdbTableIdentifier tableId(L"public", L"test_table");
		TableTransactionScanner* scanner = trx->getTableTransactionScanner(&tableId, nullptr); __STP(scanner);
		scanner->start();

		while(scanner->hasNext()){
			const CdbRecord* rec = scanner->next();
			listout.addElement((CdbRecord*)rec->copy());
		}
	}

	bool eq = listequals(list, listout);
	CHECK(eq);
}

TEST(TestScanPartGroup, trxcacheScan){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	ArrayList<CdbRecord> list; list.setDeleteOnExit();
	ArrayList<CdbRecord> listout; listout.setDeleteOnExit();

	initDb(db, dbDir);

	{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);
		insertRecord(trx, 1, L"tanaka", &list);


		trx->commit();
	}


	{
		CdbTransaction* trx = db.newTransaction(); __STP(trx);

		insertRecord(trx, 2, L"yamada", &list);
		insertRecord(trx, 3, L"yamamoto", &list);

		CdbTableIdentifier tableId(L"public", L"test_table");
		TableTransactionScanner* scanner = trx->getTableTransactionScanner(&tableId, nullptr); __STP(scanner);
		scanner->start();

		while(scanner->hasNext()){
			const CdbRecord* rec = scanner->next();
			listout.addElement((CdbRecord*)rec->copy());
		}
	}

	bool eq = listequals(list, listout);
	CHECK(eq);
}

TEST(TestScanPartGroup, rootScanCondition){
	RootScanCondition cnd;
}
