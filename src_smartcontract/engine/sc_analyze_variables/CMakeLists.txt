

set(__src
	MemberVariableEntry.cpp
	MemberVariableTable.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract engine/sc_analyze_variables)

