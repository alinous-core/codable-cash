

set(__src
	AbstractCdbValue.cpp
	CdbByteValue.cpp
	CdbIntValue.cpp
	CdbLongValue.cpp
	CdbOidValueList.cpp
	CdbOidValueListCursor.cpp
	CdbShortValue.cpp
	CdbStringValue.cpp
	VmInstanceValueConverter.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db table_record_value)

