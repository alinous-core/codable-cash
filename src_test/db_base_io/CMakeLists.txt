
set(src
	testmain.cpp
)

set(testsrc
	test_byte_buffer.cpp
	test_char_buffer.cpp
	test_exceptions.cpp
	test_file.cpp
)
set_parentv("${testsrc}" db_base_io db_base_io_test_src)

#[[
add_executable(db_base_io_test ${src} ${testsrc})
target_link_libraries(db_base_io_test codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})
#add_test(db_base_io_test db_base_io_test -v)
]]#

set(gnodir ${CMAKE_BINARY_DIR}/src_test/CMakeFiles/testall.dir/db_base_io/)
outgcov(report_test_db_base_io ${gnodir} "${testsrc}")

