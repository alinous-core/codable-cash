
set(testsrc
	test_byte_buffer.cpp
	test_char_buffer.cpp
	test_exceptions.cpp
	test_file.cpp
)
handle_sub(testall "${testsrc}" test db_base_io)

