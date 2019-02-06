/*
 * test_exp.cpp
 *
 *  Created on: 2019/02/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "compiler/SmartContractParser.h"

#include "base/StackRelease.h"
#include "sc_expression/NullLiteral.h"

#include "alinous_lang/AlinousLang.h"

TEST_GROUP(TestExpressionGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestExpressionGroup, literal01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/null.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	NullLiteral* lit = lang->nullLiteral(); __STP(lit);

	CHECK(!parser.hasError())
}



