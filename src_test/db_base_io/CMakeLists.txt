
set(testsrc
	test_byte_buffer.cpp
	test_char_buffer.cpp
	test_exceptions.cpp
	test_file.cpp
)
set_parentv("${testsrc}" db_base_io db_base_io_test_src)


set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_test/db_base_io)
outgcov(report_test_db_base_io ${gnodir} "${testsrc}")

