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

TEST(TestSQLExpressionGroup, literal){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/literal.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, boolliteral){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/boolliteral.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, colid){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/colid.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, between){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/between.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, isnull){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/isnull.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, in01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/in01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, like01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/like01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, holder){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/holder.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, func01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/func01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, add01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/add01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, mul01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/mul01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, not01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/not01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, or01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/or01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestSQLExpressionGroup, rational01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/sqlexp/rational01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractSQLExpression* exp = lang->sqlExpression(); __STP(exp);

	CHECK(!parser.hasError())
}

