

set(__src
	CdbDataFactory.cpp
	CdbKeyFactory.cpp
	CdbRecord.cpp
	CdbTableIdentifier.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db table_record)

