
set(testsrc
	test_from_section.cpp
	test_joinpart_misc.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_analyze)
