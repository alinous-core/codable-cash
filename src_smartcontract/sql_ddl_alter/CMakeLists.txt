

set(__src
	AbstractAlterDdlCommand.cpp
	AlterAddIndexCommand.cpp
	AlterAddIndexCommand.cpp
	AlterDropColumnCommand.cpp
	AlterDropIndexCommand.cpp		
)

handle_sub(codablecashlib "${__src}" smartcontract sql_ddl_alter)

