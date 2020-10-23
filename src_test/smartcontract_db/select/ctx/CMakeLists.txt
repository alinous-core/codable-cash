
set(testsrc
	test_join_conditions.cpp
	test_join_scan_cost.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/select/ctx)
