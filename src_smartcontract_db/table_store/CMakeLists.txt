

set(__src
	CdbStorageManager.cpp
	IndexStore.cpp
	RecordStore.cpp
	TableStore.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db table_store)

