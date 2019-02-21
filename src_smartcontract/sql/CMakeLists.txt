

set(__src
	AbstractSQLExpression.cpp
	AbstractSQLPart.cpp
	AbstractSQLStatement.cpp
	ISQLElement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql)

