
set(testsrc
	test_byte_buffer.cpp
	test_char_buffer.cpp
	test_exceptions.cpp
	test_file.cpp
	test_reverse_byte_buffer.cpp
)
handle_sub(testall "${testsrc}" test db/db_base_io)

