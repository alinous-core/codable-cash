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

#include "transaction/CdbTransaction.h"

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/TransactionLogFactory.h"
#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "table_record/CdbTableIdentifier.h"
#include "table_record/CdbRecord.h"

#include "table_record_value/AbstractCdbValue.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"

#include "table_record_local/LocalOidFactory.h"
#include "table_record_local/LocalCdbOid.h"

#include "table_store/CdbStorageManager.h"
#include "table_store/TableStore.h"

#include "scan_select/scan/RecordScanner.h"

#include "../toolkit/TestDbSchema01.h"
#include "sql_join_parts/TableIdentifier.h"

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

