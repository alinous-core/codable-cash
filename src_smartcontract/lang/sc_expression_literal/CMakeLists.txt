

set(__src
	BooleanLiteral.cpp
	LiteralExpression.cpp
	NullLiteral.cpp
	NumberLiteral.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_expression_literal)

