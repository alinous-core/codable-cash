

set(__src
	ColumnModifyContext.cpp
	TableRenameContext.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db schema_alter_ctx)

