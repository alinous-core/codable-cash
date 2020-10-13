

set(__src
	AlterRecordValueExecutor.cpp
	CdbStorageManager.cpp
	IndexStore.cpp
	RecordStore.cpp
	RecordValueConverter.cpp
	TableStore.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema_table/table_store)

