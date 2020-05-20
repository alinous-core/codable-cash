

set(__src
	AbstractCdbValue.cpp
	CdbByteValue.cpp
	CdbIntValue.cpp
	CdbLongValue.cpp
	CdbShortValue.cpp
	CdbStringValue.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db table_record_value)

