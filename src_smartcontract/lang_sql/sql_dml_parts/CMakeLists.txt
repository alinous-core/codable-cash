

set(__src
	SQLColumnsList.cpp
	SQLFrom.cpp
	SQLGroupBy.cpp
	SQLHaving.cpp
	SQLLimitOffset.cpp
	SQLOrderBy.cpp
	SQLSelectTarget.cpp
	SQLSelectTargetList.cpp
	SQLSet.cpp
	SQLSetPair.cpp
	SQLWhere.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang_sql/sql_dml_parts)

