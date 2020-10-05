/*
 * test_exec_alter_modify_err.cpp
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

#include "sc_analyze/AnalyzeContext.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema/SchemaManager.h"
#include "schema/SchemaAlterCommandsHandler.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTableIndex.h"

#include "ext_binary/ExtExceptionObject.h"

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

#include "sc_analyze/ValidationError.h"

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

#include "../toolkit_alter/TestDbSchemaAlterText01.h"

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestExecAlterMofdifyErrGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};


/**
 * default value error
 * ALTER TABLE test_table MODIFY email_id VARCHAR(-1);
 */
TEST(TestExecAlterMofdifyErrGroup, case01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_err/case01.alns"))
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

		vm->hasAnalyzeError(ValidationError::DB_LENGTH_IS_NOT_CORRECT_INTEGER);
	}
}

/**
 * default value error
 * ALTER TABLE test_table MODIFY email_id VARCHAR(true);
 */
TEST(TestExecAlterMofdifyErrGroup, case02){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_err/case02.alns"))
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

		vm->hasAnalyzeError(ValidationError::DB_LENGTH_IS_NOT_CORRECT_INTEGER);
	}
}

/**
 * default value error
 * ALTER TABLE test_table MODIFY email_id VARCHAR('test');
 */
TEST(TestExecAlterMofdifyErrGroup, case03){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_err/case03.alns"))
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

		vm->hasAnalyzeError(ValidationError::DB_LENGTH_IS_NOT_CORRECT_INTEGER);
	}
}

/**
 * ALTER TABLE test_table MODIFY name222 int;
 */
TEST(TestExecAlterMofdifyErrGroup, case04){
	TestDbSchemaAlterText01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_err/case04.alns"))
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

		SchemaAlterCommandsHandler handler(tester.getDatabase());

		AbstractAlterDdlCommand* cmd = stmt->getCmd();
		AlterModifyCommandLog* log = dynamic_cast<AlterModifyCommandLog*>(cmd->getCommandLog()); __STP(log);

		TableIdentifier* table = new TableIdentifier(*stmt->getTableId()); __STP(table);
		if(table->getSchema() == nullptr){
			table->setSchema(new UnicodeString(vm->getCurrentSchema()));
		}
		log->setTableIdentifier(table);

		CdbException* ex = nullptr;
		try{
			handler.handleAlterTableModify(log);
		}
		catch(CdbException* e){
			ex = e;
		}

		CHECK(ex != nullptr);
		delete ex;
	}
}

