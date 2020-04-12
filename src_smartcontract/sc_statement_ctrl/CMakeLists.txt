

set(__src
	BreakStatement.cpp
	ContinueStatement.cpp
	DoWhileStatement.cpp
	ForStatement.cpp
	IfStatement.cpp
	ReturnStatement.cpp
	ThrowStatement.cpp
	TryStatement.cpp
	WhileStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_statement_ctrl)

