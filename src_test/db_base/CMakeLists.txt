
set(src
	testmain.cpp
)

set(testsrc
	test_arraylist.cpp
	test_bitset.cpp
	test_character.cpp
	test_exceptions.cpp
	test_hashmap.cpp
	test_integer.cpp
	test_misc.cpp
	test_primitive_array.cpp
	test_stack_release.cpp
	test_thread.cpp
	test_unicode_string.cpp
)

foreach(loop_var IN LISTS testsrc)
	list(APPEND __testsrc db_base/${loop_var})
endforeach()
set(db_base_test_src ${__testsrc} PARENT_SCOPE)


add_executable(db_base_test ${src} ${testsrc})
target_link_libraries(db_base_test codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})

#add_test(testdbbase db_base_test -v)


set(target_name report_test_db_base)
set(gnodir ${CMAKE_BINARY_DIR}/src_test/CMakeFiles/testall.dir/db_base/)

outgcov(${target_name} ${gnodir} ${testsrc})



