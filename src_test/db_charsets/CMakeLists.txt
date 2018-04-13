
set(src
	testmain.cpp
)

set(db_base_io_test_src
	test_charsets.cpp
)

set(testtarget db_charset_test)

add_executable(${testtarget} ${src} ${db_base_io_test_src})
target_link_libraries(${testtarget} codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})

add_test(${testtarget} ${testtarget} -v)



