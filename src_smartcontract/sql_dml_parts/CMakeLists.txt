

set(__src
	SQLColumnsList.cpp
	SQLFrom.cpp
	SQLGroupBy.cpp
	SQLHaving.cpp
	SQLJoin.cpp
	SQLLimitOffset.cpp
	SQLOrderBy.cpp
	SQLSelectTarget.cpp
	SQLSelectTargetList.cpp
	SQLSet.cpp
	SQLSetPair.cpp
	SQLWhere.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_dml_parts)

