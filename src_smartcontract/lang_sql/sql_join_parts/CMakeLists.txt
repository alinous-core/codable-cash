

set(__src
	ParenthesisJoinPart.cpp
	SQLJoin.cpp
	SQLJoinPart.cpp
	TableIdentifier.cpp
	TableList.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang_sql/sql_join_parts)

