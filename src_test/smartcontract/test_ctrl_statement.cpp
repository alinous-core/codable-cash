/*
 * test_ctrl_statement.cpp
 *
 *  Created on: 2019/02/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "compiler/SmartContractParser.h"
#include "base/StackRelease.h"
#include "alinous_lang/AlinousLang.h"


TEST_GROUP(TestCtrlStatementGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestCtrlStatementGroup, if01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement_ctrl/if.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	IfStatement* lit = lang->ifStatement(); __STP(lit);

	CHECK(!parser.hasError())
}
