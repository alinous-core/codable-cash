/*
 * test_sql_exp.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"
#include "compiler/SmartContractParser.h"
#include "sc_statement/AbstractStatement.h"

#include "base/StackRelease.h"
#include "alinous_lang/AlinousLang.h"

TEST_GROUP(TestSQLExpressionGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestSQLExpressionGroup, tableId){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/tableid.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	TableIdentifier* tableId = lang->tableIdentifier(); __STP(tableId);

	CHECK(!parser.hasError())
}

