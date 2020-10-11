

set(__src
	AbstractAlterDdlCommand.cpp
	AbstractAlterDdlWithTypeDesc.cpp
	AlterAddColumnCommand.cpp
	AlterAddIndexCommand.cpp
	AlterDropColumnCommand.cpp
	AlterDropIndexCommand.cpp	
	IndexChecker.cpp	
)

handle_sub(codablecashlib "${__src}" smartcontract sql_ddl_alter)

