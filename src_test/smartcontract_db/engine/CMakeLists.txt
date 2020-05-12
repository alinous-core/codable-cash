
set(testsrc
	test_get_transaction.cpp
	test_sql_engine.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/engine)
