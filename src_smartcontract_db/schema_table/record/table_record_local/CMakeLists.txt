

set(__src
	LocalOidFactory.cpp
	LocalCdbOid.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema_table/record/table_record_local)

