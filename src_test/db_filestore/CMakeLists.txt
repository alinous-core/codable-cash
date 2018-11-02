
set(testsrc
	test_block_filestore.cpp
	test_filestore.cpp
	test_longrange.cpp
)
handle_sub(testall "${testsrc}" test db_filestore)

