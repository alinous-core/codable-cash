

set(__src
	CdbTable.cpp
	ColumnIndexMatcher.cpp
	CdbTableColumn.cpp
	CdbTableIndex.cpp
	TableObjectFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema_table/table)

