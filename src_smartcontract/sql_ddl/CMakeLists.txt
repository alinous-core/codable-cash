

set(__src
	CreateTableStatement.cpp
	DropTableStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_ddl)

