

set(__src
	InsertRecordsCacheCursor.cpp
	TransactionTableUpdateCache.cpp
	TransactionUpdateCache.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_update_cache)

