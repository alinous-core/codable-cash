
set(testsrc
	test_from_section.cpp
	test_scan_columns_exp_part.cpp
	test_scan_columns_part.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/select/table_analyze)
