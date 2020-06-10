

set(__src
	AbstractTransactionScanner.cpp
	TableTransactionScan.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_scanner)

