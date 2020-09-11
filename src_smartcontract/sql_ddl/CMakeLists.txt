

set(__src
	AlterTableStatement.cpp
	ColumnTypeDescriptor.cpp
	CreateTableStatement.cpp
	DdlColumnDescriptor.cpp
	DropTableStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_ddl)

