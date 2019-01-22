
set(testsrc
	test_big_decimal.cpp
	test_big_integer.cpp
	test_conversion.cpp
	test_mul.cpp
)
handle_sub(testall "${testsrc}" test db/db_numeric)

