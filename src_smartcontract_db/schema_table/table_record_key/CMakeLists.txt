

set(__src
	AbstractCdbKey.cpp
	CdbByteKey.cpp
	CdbIntKey.cpp
	CdbLongKey.cpp
	CdbOidKey.cpp
	CdbRecordKey.cpp
	CdbShortKey.cpp
	CdbStringKey.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema_table/table_record_key)

