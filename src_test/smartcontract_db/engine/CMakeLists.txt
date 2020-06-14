
set(testsrc
	DummyErrorTransactionLog.cpp
	test_get_transaction.cpp
	test_log_binary.cpp
	test_sql_engine.cpp
	test_transaction_error.cpp
	test_transaction_fw.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/engine)
