
set(testsrc
	test_condition_index_script.cpp
	test_index_conditions.cpp
	test_index_resolver.cpp
	test_join_conditions.cpp
	test_join_scan_cost.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/select/ctx)
