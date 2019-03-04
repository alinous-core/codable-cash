

set(__src
	ParenthesisJoinPart.cpp
	SQLJoin.cpp
	SQLJoinPart.cpp
	TableIdentifier.cpp
	TableList.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_join_parts)

