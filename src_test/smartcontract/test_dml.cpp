/*
 * test_dml.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "compiler/SmartContractParser.h"
#include "sc_statement/AbstractStatement.h"

#include "base/StackRelease.h"
#include "alinous_lang/AlinousLang.h"

TEST_GROUP(TestDMLGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestDMLGroup, createTable01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/dml/delete.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}
