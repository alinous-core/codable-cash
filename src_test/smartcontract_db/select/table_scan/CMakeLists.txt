
set(testsrc
	test_index_record_scanner.cpp
	test_index_scanner.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/select/table_scan)
