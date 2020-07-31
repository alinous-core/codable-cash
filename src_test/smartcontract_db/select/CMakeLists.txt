
set(testsrc
	test_condition_misc.cpp
	test_select_arithmetic_contition.cpp
	test_select_contition.cpp
	test_select_logic_contition.cpp
	test_select01.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/select)
