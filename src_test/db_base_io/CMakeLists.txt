
set(src
	testmain.cpp
)

set(db_base_io_test_src
	test_byte_buffer.cpp
	test_char_buffer.cpp
	test_file.cpp
)

add_executable(db_base_io_test ${src} ${db_base_io_test_src})
target_link_libraries(db_base_io_test codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})

add_test(db_base_io_test db_base_io_test -v)



