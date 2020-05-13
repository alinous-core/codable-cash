

set(__src
	CdbTable.cpp
	CdbTableColumn.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db table)

