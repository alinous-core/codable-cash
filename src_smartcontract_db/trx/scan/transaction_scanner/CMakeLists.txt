

set(__src
	AbstractTransactionScanner.cpp
	TableTransactionScanner.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db trx/scan/transaction_scanner)

