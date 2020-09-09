

set(__src
	AlterAddPrimaryKeyCommand.cpp
	AlterDropPrimaryKeyCommand.cpp
	AlterModifyCommand.cpp
	AlterRenameColumnCommand.cpp
	AlterRenameTableCommand.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_ddl_alter_modify)

