

set(__src
	BreakStatement.cpp
	ContinueStatement.cpp
	DoWhileStatement.cpp
	ForStatement.cpp
	IfStatement.cpp
	ReturnStatement.cpp
	WhileStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_statement_ctrl)

