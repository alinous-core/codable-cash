
set(testsrc
	test_filestore.cpp
	test_longrange.cpp
)
handle_sub(testall "${testsrc}" test db_filestore)

