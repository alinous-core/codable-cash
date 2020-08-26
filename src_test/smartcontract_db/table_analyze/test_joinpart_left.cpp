/*
 * test_joinpart_left.cpp
 *
 *  Created on: 2020/08/26
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../toolkit/TestDbSchema01.h"
#include "compiler/SmartContractParser.h"
#include "alinous_lang/AlinousLang.h"

#include "sc_analyze/AnalyzeContext.h"

using namespace codablecash;

TEST_GROUP(TestJoinPartLeftGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};


TEST(TestJoinPartLeftGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/joinleft/case01/select01.alns"))

	TestDbSchema01 schem(this->env);
	schem.init();

	VirtualMachine* vm = schem.getVm();
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);
	}
}
