/*
 * test_scan_columns_part.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "base_io/File.h"

#include "scan_columns/AllScanColumns.h"
#include "scan_columns/ScanColumn.h"

#include "vm/VirtualMachine.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"

#include "sql_dml_parts/SQLSelectTargetList.h"

#include "sc_analyze/AnalyzeContext.h"
using namespace codablecash;

TEST_GROUP(TestScanColumnsPartGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};


TEST(TestScanColumnsPartGroup, case01){
	AllScanColumns cols;
}

TEST(TestScanColumnsPartGroup, case02){
	ScanColumn col;
	const UnicodeString t(L"t");

	col.setAsName(&t);
}

TEST(TestScanColumnsPartGroup, select01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns/select01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		selectList->analyze(actx);

		// FIXME testing now
	}
}
