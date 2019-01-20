
set(testsrc
	test_block_filestore.cpp
	test_filestore.cpp
	test_longrange.cpp
	test_longrange_binary.cpp
)
handle_sub(testall "${testsrc}" test db/db_filestore)

