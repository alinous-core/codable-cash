

set(__src
	DeletedOidsRepository.cpp
	DeletedRecordsOidsCursor.cpp
	InsertedRecordsRepository.cpp
	InsertRecordsCacheCursor.cpp
	TransactionTableUpdateCache.cpp
	TransactionUpdateCache.cpp
	UpdatedRecordCursor.cpp
	UpdatedRecordsRepository.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_update_cache)

