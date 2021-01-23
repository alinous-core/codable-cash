/*
 * test_join_conditions_index.cpp
 *
 *  Created on: 2020/12/17
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "../../toolkit_join/TestDbSchemaJoin01.h"

#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "lang_sql/sql_expression/SQLColumnIdentifier.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "scan_select/scan_planner/scanner/join/JoinCandidate.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/TablesHolder.h"

#include "scan_select/scan_table/TableScanTarget.h"

#include "schema_table/table/CdbTableIndex.h"


using namespace codablecash;


TEST_GROUP(TestJoinConditionIndexGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestJoinConditionIndexGroup, case01){
	TestDbSchemaJoin01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		TablesHolder* tableHolder = planner->getTablesHolder();
		TableScanTarget* target = tester.getScanTarget(L"public", L"test_table");
		tableHolder->addScanTarget(target);
		target = tester.getScanTarget(L"public", L"emails");
		tableHolder->addScanTarget(target);

		SQLColumnIdentifier id(L"public", L"test_table", L"email_id");
		SQLColumnIdentifier email_id(L"public", L"emails", L"email_id");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pemail_id(&email_id);

		pid.analyzeConditions(vm, planner);
		pemail_id.analyzeConditions(vm, planner);

		JoinCandidate candidate(JoinCandidate::INNER, &pid, &pemail_id);

		const AbstractScanTableTarget* starget = pemail_id.getTarget();
		CdbTableIndex* index = candidate.getIndex(starget);

		const UnicodeString* indexStr = index->getName();
		UnicodeString ans(L"idx_emails_email_id");
		CHECK(ans.equals(indexStr));

		starget = pid.getTarget();
		index = candidate.getIndex(starget);
		CHECK(index == nullptr);
	}
}
