

set(__src
	AbstractDdlLog.cpp
	AbstractTransactionLog.cpp
	CreateTableLog.cpp
	DropTableLog.cpp
	InsertLog.cpp
	TransactionLogFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db trx/transaction_log)

