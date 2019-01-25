
set(__src
	FeeIndex.cpp
	FeeIndexKey.cpp
	FeeIndexKeyFactory.cpp
	FeeTransactionsListValue.cpp
	FeeTransactionsListValueFactory.cpp
)
handle_sub(codablecashlib "${__src}" blockchain mempool_idx)
