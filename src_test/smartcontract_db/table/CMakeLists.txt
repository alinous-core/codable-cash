
set(testsrc
	test_binary_object_check_error.cpp
	test_cdb_key_values.cpp
	test_cdb_values.cpp
	test_create_table_script.cpp
	test_create_table.cpp
	test_insert_parts_types.cpp
	test_insert_parts.cpp
	test_insert.cpp
	test_metadata.cpp
	test_scan_part.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table)
