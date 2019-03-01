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

TEST(TestExpressionGroup, literalbool){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/bool.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	BooleanLiteral* lit = lang->booleanLiteral(); __STP(lit);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, literal02){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/lit.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* lit = lang->literal(); __STP(lit);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, literalNumber){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/num.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* lit = lang->literal(); __STP(lit);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, notexp){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/not.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, bitrevexp){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/bitrev.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, preinc){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/preinc.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, postinc){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/postinc.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, cast){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/cast.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, alloc){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/alloc.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, arrayRef){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/arrayRef.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionGroup, mamberRef){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression/mamberRef.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

