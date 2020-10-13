

set(__src
	AbstractArithmeticBinaryExpresson.cpp
	AbstractArithmeticExpression.cpp
	AddExpression.cpp
	MultiplicativeExpression.cpp
	NegateExpression.cpp
	PostIncrementExpression.cpp
	PreIncrementExpression.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_expression_arithmetic)

