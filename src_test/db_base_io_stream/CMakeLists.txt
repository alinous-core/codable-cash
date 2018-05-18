
set(testsrc
	test_exceptions.cpp
	test_file_stream.cpp
	test_reader.cpp
)
handle_sub(testall "${testsrc}" test db_base_io_stream)

