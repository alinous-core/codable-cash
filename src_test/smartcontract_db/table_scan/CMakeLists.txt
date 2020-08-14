
set(testsrc
	test_index_scanner.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_scan)
