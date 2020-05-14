

set(__src
	CdbTable.cpp
	CdbTableColumn.cpp
	CdbTableIndex.cpp
	TableObjectFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db table)

