

set(__src
	Schema.cpp
	SchemaBinary.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema)

