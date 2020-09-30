/*
 * test_exec_alter_modify_unique.cpp
 *
 *  Created on: 2020/09/30
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


TEST_GROUP(TestExecAlterMofdifyUniqueGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};


/**
 * Add unique error
 */
TEST(TestExecAlterMofdifyUniqueGroup, case01){

}

/**
 * set primary key unique
 */
TEST(TestExecAlterMofdifyUniqueGroup, case02){

}

/**
 * set primary key not unique
 */
TEST(TestExecAlterMofdifyUniqueGroup, case03){

}
