

set(__src
	AbstractTransactionLog.cpp
	CreateTableLog.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_log)

