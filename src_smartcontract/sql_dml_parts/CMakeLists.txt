

set(__src
	SQLColumnsList.cpp
	SQLFrom.cpp
	SQLGroupBy.cpp
	SQLLimitOffset.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_dml_parts)

