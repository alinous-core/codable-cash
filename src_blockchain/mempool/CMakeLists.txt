
set(__src
	FeeIndex.cpp
	FeeIndexKey.cpp
	FeeIndexKeyFactory.cpp
	FeeTransactionsListValue.cpp
	FeeTransactionsListValueFactory.cpp
	FposValue.cpp
	IndexValueFactory.cpp
	MemPool.cpp
	TransactionIdIndex.cpp
	TransactionIdKey.cpp
	TransactionIdKeyFactory.cpp
	TransactionRecord.cpp
	TransactionStore.cpp
)
handle_sub(codablecashlib "${__src}" blockchain mempool)
