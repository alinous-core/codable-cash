
set(testsrc
	test_from_section.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_analyze)
