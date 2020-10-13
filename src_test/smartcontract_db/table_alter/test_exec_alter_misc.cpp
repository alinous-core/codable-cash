/*
 * test_exec_alter_misc.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"
#include "../toolkit/TestDbSchema01.h"
#include "../toolkit_alter/TestDbSchemaAlter01.h"
#include "../toolkit_alter/TestDbSchemaAlter02.h"
#include "../toolkit_alter/TestDbSchemaAlter03.h"

#include "sc_analyze/AnalyzeContext.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"
#include "schema_table/table/CdbTableIndex.h"

#include "trx/transaction_log_alter/AbstractAlterCommandLog.h"

#include "trx/transaction/CdbTransactionManager.h"

TEST_GROUP(TestExecAlterMiscGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

class DummyCommand : public AbstractAlterCommandLog {
public:
	explicit DummyCommand() : AbstractAlterCommandLog(123) {
	}
	virtual ~DummyCommand(){};
	virtual void initCommandParam(VirtualMachine* vm, TableIdentifier* tableId){}
	virtual void commit(CdbTransactionManager* trxManager){}
};

TEST(TestExecAlterMiscGroup, misc01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	CodableDatabase* db = tester.getDatabase();
	CdbTransactionManager* trxManager = db->getTransactionxManager();

	DummyCommand* cmd = new DummyCommand(); __STP(cmd);

	CdbException* ex = nullptr;
	try{
		trxManager->commitAlterTable(cmd);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

