

set(__src
	SQLAdditiveExpression.cpp
	SQLAndExpression.cpp
	SQLBooleanLiteral.cpp
	SQLColumnIdentifier.cpp
	SQLEqualityExpression.cpp
	SQLExpressionList.cpp
	SQLInExpression.cpp
	SQLIsNullExpression
	SQLLikeExpression.cpp
	SQLLiteral.cpp
	SqlMultiplicativeExpression.cpp
	SQLNotExpression.cpp
	SQLOrExpression.cpp
	SQLParenthesisExpression.cpp
	SQLRelationalExpression.cpp
	TableIdentifier.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_expression)

