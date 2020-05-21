

set(__src
	AbstractCdbKey.cpp
	CdbByteKey.cpp
	CdbIntKey.cpp
	CdbLongKey.cpp
	CdbShortKey.cpp
	CdbStringKey.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db table_record_key)

