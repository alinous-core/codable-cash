

set(__src
	FunctionScoreCalc.cpp
	MethodScore.cpp
	VTable.cpp
	VTableClassEntry.cpp
	VTableRegistory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc_analyze_functions)

