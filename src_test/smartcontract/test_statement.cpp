/*
 * test_statement.cpp
 *
 *  Created on: 2019/03/01
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "compiler/SmartContractParser.h"

#include "base/StackRelease.h"
#include "sc_expression/NullLiteral.h"

#include "alinous_lang/AlinousLang.h"

TEST_GROUP(TestStatementGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStatementGroup, substitute01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/substitute01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

TEST(TestStatementGroup, valdec01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/valdec01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

TEST(TestStatementGroup, blank){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/blank.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

TEST(TestStatementGroup, expstatement){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/expstatement.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

