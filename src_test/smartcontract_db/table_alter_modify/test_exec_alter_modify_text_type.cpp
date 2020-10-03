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
#include "table_record_value/CdbStringValue.h"

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

static bool checkTextValue(const AbstractCdbValue* cdbv, const wchar_t* ans);
bool checkTextValue(const AbstractCdbValue* cdbv, const wchar_t* ans){
	if(ans == nullptr){
		return cdbv == nullptr;
	}

	const CdbStringValue* strv = dynamic_cast<const CdbStringValue*>(cdbv);
	const UnicodeString* str = strv->getValue();

	UnicodeString ansstr(ans);

	return ansstr.equals(str);
}

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
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_text/case01.alns"))
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
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_text/case02.alns"))
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
 * text change length(shorter) including null
 * ALTER TABLE test_table MODIFY name VARCHAR(2) UNIQUE;
 */
TEST(TestExecAlterMofdifyTextGroup, case02){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*512);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_text/case03.alns"))
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
		CHECK(t == AbstractCdbValue::TYPE_STRING);

		CHECK(!col->isNotnull());
		CHECK(col->isUnique());

		ArrayList<CdbRecord>* list = tester.scanRecords(L"test_table"); __STP(list);
		list->setDeleteOnExit();

		int maxLoop = list->size();
		CHECK(maxLoop == 4);

		int pos = col->getPosition();
		CHECK(pos == 1);

		bool result = false;
		for(int i = 0; i != maxLoop; ++i){
			CdbRecord* record = list->get(i);

			const AbstractCdbValue* cdbv = record->get(pos);

			switch(i){
			case 0:
				result = checkTextValue(cdbv, L"ta");
				CHECK(result);
				break;
			case 1:
				result = checkTextValue(cdbv, L"sa");
				CHECK(result);
				break;
			case 2:
				result = checkTextValue(cdbv, nullptr);
				CHECK(result);
				break;
			case 3:
			default:
				result = checkTextValue(cdbv, L"10");
				CHECK(result);
				break;
			}
		}
	}
}

/**
 * unique error on text change length(shorter)
 * ALTER TABLE test_table MODIFY name VARCHAR(2) UNIQUE;
 */
TEST(TestExecAlterMofdifyTextGroup, case03_err){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*512);
	tester.insert02();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_text/case03.alns"))
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
 * text change length(longer)
 * ALTER TABLE test_table MODIFY name VARCHAR(255) UNIQUE;
 */
TEST(TestExecAlterMofdifyTextGroup, case04){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*512);
	tester.insert03();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_text/case04.alns"))
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
		CHECK(t == AbstractCdbValue::TYPE_STRING);
		int len = col->getLength();
		CHECK(len == 255);

		CHECK(!col->isNotnull());
		CHECK(col->isUnique());

		ArrayList<CdbRecord>* list = tester.scanRecords(L"test_table"); __STP(list);
		list->setDeleteOnExit();

		int maxLoop = list->size();
		CHECK(maxLoop == 4);

		int pos = col->getPosition();
		CHECK(pos == 1);

		bool result = false;
		for(int i = 0; i != maxLoop; ++i){
			CdbRecord* record = list->get(i);

			const AbstractCdbValue* cdbv = record->get(pos);

			switch(i){
			case 0:
				result = checkTextValue(cdbv, L"tanaka");
				CHECK(result);
				break;
			case 1:
				result = checkTextValue(cdbv, L"sato");
				CHECK(result);
				break;
			case 2:
				result = checkTextValue(cdbv, L"saito");
				CHECK(result);
				break;
			case 3:
			default:
				result = checkTextValue(cdbv, nullptr);
				CHECK(result);
				break;
			}
		}
	}
}

/**
 * text change length(longer)
 * ALTER TABLE test_table MODIFY name TEXT UNIQUE;
 */
TEST(TestExecAlterMofdifyTextGroup, case05){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*512);
	tester.insert03();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_text/case05.alns"))
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
		CHECK(t == AbstractCdbValue::TYPE_STRING);
		int len = col->getLength();
		CHECK(len == 0);

		CHECK(!col->isNotnull());
		CHECK(col->isUnique());

		ArrayList<CdbRecord>* list = tester.scanRecords(L"test_table"); __STP(list);
		list->setDeleteOnExit();

		int maxLoop = list->size();
		CHECK(maxLoop == 4);

		int pos = col->getPosition();
		CHECK(pos == 1);

		bool result = false;
		for(int i = 0; i != maxLoop; ++i){
			CdbRecord* record = list->get(i);

			const AbstractCdbValue* cdbv = record->get(pos);

			switch(i){
			case 0:
				result = checkTextValue(cdbv, L"tanaka");
				CHECK(result);
				break;
			case 1:
				result = checkTextValue(cdbv, L"sato");
				CHECK(result);
				break;
			case 2:
				result = checkTextValue(cdbv, L"saito");
				CHECK(result);
				break;
			case 3:
			default:
				result = checkTextValue(cdbv, nullptr);
				CHECK(result);
				break;
			}
		}
	}
}
