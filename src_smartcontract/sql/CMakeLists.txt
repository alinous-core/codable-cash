

set(__src
	AbstractSQLExpression.cpp
	AbstractSQLStatement.cpp
	ISQLElement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql)

