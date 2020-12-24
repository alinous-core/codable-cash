

set(__src
	RightTableBufferedOidTransactionScanner.cpp
	RightTableIndexTransactionScanner.cpp
	RightTableOrTransactionScanner.cpp
	RightTableBufferedTransactionScanner.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db trx/scan/transaction_scanner_join_right)

