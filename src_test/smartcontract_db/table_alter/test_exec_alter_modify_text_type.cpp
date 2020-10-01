/*
 * test_exec_alter_text_type.cpp
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"
#include "../toolkit/TestDbSchema01.h"
#include "../toolkit_alter/TestDbSchemaAlter01.h"
#include "../toolkit_alter/TestDbSchemaAlter02.h"
#include "../toolkit_alter/TestDbSchemaAlter03.h"

#include "sc_analyze/AnalyzeContext.h"

#include "engine/CodableDatabase.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTableIndex.h"


TEST_GROUP(TestExecAlterMofdifyTextGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

/**
 * text to int (includes not int)
 */
TEST(TestExecAlterMofdifyTextGroup, case01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();
}

/**
 * text change length(shorter)
 */
TEST(TestExecAlterMofdifyTextGroup, case02){

}

/**
 * text change length(longer)
 */
TEST(TestExecAlterMofdifyTextGroup, case03){

}
