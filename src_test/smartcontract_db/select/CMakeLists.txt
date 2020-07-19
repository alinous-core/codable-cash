
set(testsrc
	test_select_contition.cpp
	test_select01.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/select)
