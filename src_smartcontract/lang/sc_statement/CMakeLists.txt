

set(__src
	AbstractStatement.cpp
	BlankStatement.cpp
	ExpressionStatement.cpp
	StatementBlock.cpp
	SubstitutionStatement.cpp
	VariableDeclareStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_statement)

