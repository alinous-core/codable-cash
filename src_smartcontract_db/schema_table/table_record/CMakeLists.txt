

set(__src
	CdbDataFactory.cpp
	CdbKeyFactory.cpp
	CdbRecord.cpp
	CdbTableIdentifier.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema_table/table_record)

