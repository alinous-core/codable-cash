
set(testsrc
	test_arraylist.cpp
	test_bitset.cpp
	test_character.cpp
	test_exceptions.cpp
	test_hashmap.cpp
	test_integer.cpp
	test_linkedlist.cpp
	test_long.cpp
	test_misc.cpp
	test_primitive_array.cpp
	test_stack_release.cpp
	test_test.cpp
	test_unicode_string.cpp
)
handle_sub(testall "${testsrc}" test db/db_base)




