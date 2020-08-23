

set(__src
	AbstractJoinExecutor.cpp
	InnerJoinExecutor.cpp
	IJoinLeftSource.cpp
	IJoinRightSource.cpp
	OuterJoinExecutor.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_scanner_join)

