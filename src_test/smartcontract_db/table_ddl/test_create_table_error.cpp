/*
 * test_create_table_error.cpp
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "base_io/File.h"

#include "../toolkit/TestDbSchema01.h"

#include "vm/VirtualMachine.h"

#include "compiler/SmartContractParser.h"
#include "alinous_lang/AlinousLang.h"

#include "sql_ddl/DropTableStatement.h"

#include "sc_analyze/AnalyzeContext.h"
using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestCreateTableErrorGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestCreateTableErrorGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024*10);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_ddl/resources/create_err/case01.alns"))
	{

	}
}

