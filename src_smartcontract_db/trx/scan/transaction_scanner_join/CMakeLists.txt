

set(__src
	AbstractJoinExecutor.cpp
	InnerJoinExecutor.cpp
	IJoinLeftSource.cpp
	IJoinRightSource.cpp
	JoinCandidateCursor.cpp
	OuterJoinExecutor.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db trx/scan/transaction_scanner_join)

