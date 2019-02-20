

set(__src
	AbstractSQLBinaryExpression.cpp
	SQLAdditiveExpression.cpp
	SQLAndExpression.cpp
	SQLBetweenExpression.cpp
	SQLBooleanLiteral.cpp
	SQLColumnIdentifier.cpp
	SQLEqualityExpression.cpp
	SQLExpressionList.cpp
	SQLFunctionCall.cpp
	SQLInExpression.cpp
	SQLIsNullExpression
	SQLLikeExpression.cpp
	SQLLiteral.cpp
	SqlMultiplicativeExpression.cpp
	SQLNotExpression.cpp
	SQLOrExpression.cpp
	SQLParenthesisExpression.cpp
	SQLPlaceHolder.cpp
	SQLRelationalExpression.cpp
	TableIdentifier.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_expression)

