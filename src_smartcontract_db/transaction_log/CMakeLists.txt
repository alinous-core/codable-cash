

set(__src
	AbstractDdlLog.cpp
	AbstractTransactionLog.cpp
	CreateTableLog.cpp
	InsertLog.cpp
	TransactionLogFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_log)

