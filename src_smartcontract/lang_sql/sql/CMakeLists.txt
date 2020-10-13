

set(__src
	AbstractJoinPart.cpp
	AbstractSQLExpression.cpp
	AbstractSQLPart.cpp
	AbstractSQLStatement.cpp
	ISQLElement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang_sql/sql)

