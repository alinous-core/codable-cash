/*
 * test_schema.cpp
 *
 *  Created on: 2020/10/05
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

#include "schema_table/record/table_record/CdbTableIdentifier.h"
#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"
#include "schema_table/record/table_record_value/CdbIntValue.h"
#include "schema_table/record/table_record_value/CdbStringValue.h"

#include "schema_table/record/table_record_local/LocalOidFactory.h"
#include "schema_table/record/table_record_value/VmInstanceValueConverter.h"

#include "schema_table/table_store/CdbStorageManager.h"
#include "schema_table/table_store/TableStore.h"

#include "scan_select/scan/RecordScanner.h"

#include "smartcontract_db/toolkit/TestDbSchema01.h"
#include "lang_sql/sql_join_parts/TableIdentifier.h"

using namespace codablecash;

TEST_GROUP(TestSchemaGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestSchemaGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init();

	{
		CdbTableColumn* col = tester.getColumn(L"test_table", L"email_id2222");
		CHECK(col == nullptr);
	}
}

TEST(TestSchemaGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init();

	CdbException* ex = nullptr;
	try{
		CdbTable* table = tester.getTable(L"aaaa", L"bbbb");
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex);
	delete ex;
}

TEST(TestSchemaGroup, case03){
	TestDbSchema01 tester(this->env);
	tester.init();

	CdbException* ex = nullptr;
	try{
		CdbTable* table = tester.getTable(L"public", L"bbbb");
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex);
	delete ex;
}

TEST(TestSchemaGroup, case04){
	TestDbSchema01 tester(this->env);
	tester.init();

	{
		TableIdentifier tableId;
		tableId.setTableName(new UnicodeString(L"test_table"));

		SchemaManager* mgr = tester.getSchemaManager();

		UnicodeString defstr(L"public");
		CdbTable* table = mgr->getTable(&tableId, &defstr);

		CHECK(table != nullptr);
	}
}

