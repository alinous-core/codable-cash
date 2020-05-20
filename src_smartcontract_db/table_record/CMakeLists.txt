

set(__src
	CdbDataFactory.cpp
	CdbKeyFactory.cpp
	CdbRecord.cpp
	RecordVersionEntry.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db table_record)

