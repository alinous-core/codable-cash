

set(__src
	ColumnTypeDescriptor.cpp
	CreateTableStatement.cpp
	DdlColumnDescriptor.cpp
	DropTableStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_ddl)

