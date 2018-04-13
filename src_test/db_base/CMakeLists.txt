
set(src
	testmain.cpp
)

set(db_base_test_src
	test_thread.cpp
	test_arraylist.cpp
	test_unicode_string.cpp
)

add_executable(db_base_test ${src} ${db_base_test_src})
target_link_libraries(db_base_test codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})

add_test(testdbbase db_base_test -v)



