/*
 * test_sql_misc.cpp
 *
 *  Created on: 2020/05/10
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "engine/compiler/SmartContractParser.h"
#include "lang/sc_statement/AbstractStatement.h"

#include "base/StackRelease.h"
#include "alinous_lang/AlinousLang.h"

TEST_GROUP(TestSQLMiscGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestSQLMiscGroup, case01){
	SQLIsNullExpression nullexp;
	CHECK(nullexp.isExecutable());
}

TEST(TestSQLMiscGroup, case02){
	ColumnTypeDescriptor coldesc;
	CHECK(coldesc.isExecutable());
}


