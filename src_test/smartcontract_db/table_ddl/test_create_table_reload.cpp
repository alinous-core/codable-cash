/*
 * test_create_table_reload.cpp
 *
 *  Created on: 2020/10/04
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"
#include "base/ArrayList.h"

#include "base_io/File.h"
#include "base_io/ByteBuffer.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "trx/transaction/CdbTransaction.h"

#include "trx/transaction_log/AbstractTransactionLog.h"
#include "trx/transaction_log/TransactionLogFactory.h"
#include "trx/transaction_log/CreateTableLog.h"
#include "trx/transaction_log/InsertLog.h"

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/table_record/CdbTableIdentifier.h"
#include "schema_table/table_record/CdbRecord.h"

#include "schema_table/table_record_value/AbstractCdbValue.h"
#include "schema_table/table_record_value/CdbIntValue.h"
#include "schema_table/table_record_value/CdbStringValue.h"

#include "schema_table/table_record_local/LocalOidFactory.h"
#include "schema_table/table_record_local/LocalCdbOid.h"

#include "schema_table/table_record_value/VmInstanceValueConverter.h"

#include "schema_table/table_store/CdbStorageManager.h"
#include "schema_table/table_store/TableStore.h"

#include "scan_select/scan/RecordScanner.h"

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
static void insertRecord(CdbTransaction* trx, LocalOidFactory* lfactory, int id,	const wchar_t* name);
static ArrayList<CdbRecord>* scanRecords(CodableDatabase* db, const wchar_t* schema, const wchar_t* table);
static CdbTable* getTable(CodableDatabase* db, const wchar_t* schema, const wchar_t* table);

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

		ArrayList<CdbRecord>* list = scanRecords(&db, L"public", L"test_table"); __STP(list);
		list->setDeleteOnExit();

		int maxLoop = list->size();
		CHECK(maxLoop == 3);
		for(int i = 0; i != maxLoop; ++i){
			CdbRecord* rec = list->get(i);

			const CdbIntValue* iv = dynamic_cast<const CdbIntValue*>(rec->get(0));
			const CdbStringValue* sv = dynamic_cast<const CdbStringValue*>(rec->get(1));
			const UnicodeString* str = sv->getValue();

			switch(i){
			case 0:
				CHECK(iv->getValue() == 1);
				CHECK(str->equals(L"yamada"));
				break;
			case 1:
				CHECK(iv->getValue() == 2);
				CHECK(str->equals(L"tanaka"));
				break;
			case 2:
			default:
				CHECK(iv->getValue() == 3);
				CHECK(str->equals(L"sato"));
				break;
			}
		}
	}
}

ArrayList<CdbRecord>* scanRecords(CodableDatabase* db, const wchar_t* schema, const wchar_t* table){
	CdbStorageManager* storageMgr = db->getStorageManager();

	CdbTable* cdbtable = getTable(db, schema, table);

	TableStore* store = storageMgr->getTableStore(cdbtable->getOid());

	RecordScanner scanner(store);
	scanner.start();

	ArrayList<CdbRecord>* list = new ArrayList<CdbRecord>();
	while(scanner.hasNext()){
		const CdbRecord* record = scanner.next();

		list->addElement(new CdbRecord(*record));
	}

	return list;
}

CdbTable* getTable(CodableDatabase* db, const wchar_t* schema, const wchar_t* table){
	SchemaManager* scMgr = db->getSchemaManager();

	UnicodeString schemastr(schema);
	UnicodeString tableName(table);
	CdbTable* cdbtable = scMgr->getTable(&schemastr, &tableName);

	return cdbtable;
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
