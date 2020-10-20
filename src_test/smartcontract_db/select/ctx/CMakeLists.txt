
set(testsrc
	test_join_conditions.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/select/ctx)
