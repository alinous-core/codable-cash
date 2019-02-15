

set(__src
	AbstractStatement.cpp
	BlankStatement.cpp
	ExpressionStatement.cpp
	StatementBlock.cpp
	SubstitutionStatement.cpp
	SubstitutionStatement.cpp
	VariableDeclareStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_statement)

