
set(src
	testmain.cpp
)

set(testsrc
	test_byte_buffer.cpp
	test_char_buffer.cpp
	test_exceptions.cpp
	test_file.cpp
)

foreach(loop_var IN LISTS testsrc)
	list(APPEND __testsrc db_base_io/${loop_var})
endforeach()
set(db_base_io_test_src ${__testsrc} PARENT_SCOPE)



add_executable(db_base_io_test ${src} ${testsrc})
target_link_libraries(db_base_io_test codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})

#add_test(db_base_io_test db_base_io_test -v)

set(target_name report_test_db_base_io)
set(gnodir ${CMAKE_BINARY_DIR}/src_test/CMakeFiles/testall.dir/db_base_io/)

outgcov(${target_name} ${gnodir} ${testsrc})

