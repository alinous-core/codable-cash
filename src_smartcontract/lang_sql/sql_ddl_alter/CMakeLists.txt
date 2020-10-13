

set(__src
	AbstractAlterDdlCommand.cpp
	AbstractAlterDdlWithTypeDesc.cpp
	AlterAddColumnCommand.cpp
	AlterAddIndexCommand.cpp
	AlterDropColumnCommand.cpp
	AlterDropIndexCommand.cpp	
	IndexChecker.cpp	
)

handle_sub(codablecashlib "${__src}" smartcontract lang_sql/sql_ddl_alter)

