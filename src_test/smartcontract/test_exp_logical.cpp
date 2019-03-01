/*
 * test_exp_logical.cpp
 *
 *  Created on: 2019/03/01
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "compiler/SmartContractParser.h"

#include "base/StackRelease.h"
#include "sc_expression/NullLiteral.h"

#include "alinous_lang/AlinousLang.h"

TEST_GROUP(TestExpressionLogicalGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestExpressionLogicalGroup, and01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_logical/and01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionLogicalGroup, or01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_logical/or01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

