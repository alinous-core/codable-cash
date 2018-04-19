
set(testsrc
	test_file_stream.cpp
)
set_parentv("${testsrc}" db_base_io_stream test_base_io_stream_src)


set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_test/db_base_io_stream)
outgcov(test_base_io_stream ${gnodir} "${testsrc}")


