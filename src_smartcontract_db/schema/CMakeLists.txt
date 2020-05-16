

set(__src
	ISchemaUptateListner.cpp
	SchemaManager.cpp
	SchemaRoot.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema)

