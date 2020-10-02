/*
 * test_exec_alter_text_type.cpp
 *
 *  Created on: 2020/10/01
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
#include "../toolkit_alter/TestDbSchemaAlterText01.h"
#include "../toolkit_alter/TestDbSchemaAlterTextUnique01.h"

#include "sc_analyze/AnalyzeContext.h"

#include "engine/CodableDatabase.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTableIndex.h"

#include "table_record_value/AbstractCdbValue.h"
#include "table_record_value/CdbIntValue.h"

#include "table_record/CdbRecord.h"

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

#include "ext_binary/ExtExceptionObject.h"

using namespace codablecash;

TEST_GROUP(TestExecAlterMofdifyTextGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

/**
 * text to int (includes not int)
 * ALTER TABLE test_table MODIFY name int;
 */
TEST(TestExecAlterMofdifyTextGroup, case01){
	TestDbSchemaAlterText01 tester(this->env);
	tester.init(1024*512);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter/resources/exec_alter_modify_text/case01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		stmt->preAnalyze(actx);
		stmt->analyzeTypeRef(actx);
		stmt->analyze(actx);

		stmt->interpret(vm);

		// checking
		CdbTableColumn* col = tester.getColumn(L"test_table", L"name");
		uint8_t t = col->getType();
		CHECK(t == AbstractCdbValue::TYPE_INT);

		CHECK(!col->isNotnull());
		CHECK(!col->isUnique());

		ArrayList<CdbRecord>* list = tester.scanRecords(L"test_table"); __STP(list);
		list->setDeleteOnExit();

		int maxLoop = list->size();
		CHECK(maxLoop == 4);

		int pos = col->getPosition();
		CHECK(pos == 1);

		for(int i = 0; i != maxLoop; ++i){
			CdbRecord* record = list->get(i);

			const CdbIntValue* v = dynamic_cast<const CdbIntValue*>(record->get(pos));
			if(i == 2){
				CHECK( v == nullptr);
			}
			else if(i != 3){
				int32_t intvalue = v->getValue();
				CHECK(0 == intvalue);
			}
			else{
				int32_t intvalue = v->getValue();
				CHECK(100 == intvalue);
			}
		}
	}

}

/**
 * unique error case, after changing value
 * text to int (includes not int)
 * ALTER TABLE test_table MODIFY name int UNIQUE;
 */
TEST(TestExecAlterMofdifyTextGroup, case01_err){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*512);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter/resources/exec_alter_modify_text/case02.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		stmt->preAnalyze(actx);
		stmt->analyzeTypeRef(actx);
		stmt->analyze(actx);

		stmt->interpret(vm);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}

}


/**
 * text change length(shorter)
 *
 */
TEST(TestExecAlterMofdifyTextGroup, case02){

}

/**
 * unique error case, after changing length into shorter one
 *
 */
TEST(TestExecAlterMofdifyTextGroup, case02_err){

}

/**
 * text change length(longer)
 */
TEST(TestExecAlterMofdifyTextGroup, case03){

}
