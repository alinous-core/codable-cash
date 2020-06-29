

set(__src
	AbstractJsonExpression.cpp
	JsonArrayExpression.cpp
	JsonInitializerExpression.cpp
	JsonKeyValuePairExpression.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_expression_json)

