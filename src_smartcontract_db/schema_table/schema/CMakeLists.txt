

set(__src
	ISchemaUptateListner.cpp
	Schema.cpp
	SchemaAlterCommandsHandler.cpp
	SchemaManager.cpp
	SchemaRoot.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema_table/schema)

