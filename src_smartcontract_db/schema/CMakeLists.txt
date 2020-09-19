

set(__src
	ColumnModifyContext.cpp
	ISchemaUptateListner.cpp
	Schema.cpp
	SchemaManager.cpp
	SchemaRoot.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema)

