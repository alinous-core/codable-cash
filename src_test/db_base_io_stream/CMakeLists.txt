
set(testsrc
	test_file_stream.cpp
)
handle_sub(testall "${testsrc}" test db_base_io_stream)

