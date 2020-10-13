

set(__src
	AndExpression.cpp
	BitReverseExpression.cpp
	ExclusiveOrExpression.cpp
	OrExpression.cpp
	ShiftExpression.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_expression_bit)

