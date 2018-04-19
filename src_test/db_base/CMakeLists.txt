
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

set_parentv("${testsrc}" db_base db_base_test_src)

#[[
add_executable(db_base_test ${src} ${testsrc})
target_link_libraries(db_base_test codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})
#add_test(testdbbase db_base_test -v)
]]#


set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_test/db_base)
outgcov(report_test_db_base ${gnodir} "${testsrc}")



