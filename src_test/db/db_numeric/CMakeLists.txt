
set(testsrc
	test_big_decimal.cpp
)
handle_sub(testall "${testsrc}" test db/db_numeric)

