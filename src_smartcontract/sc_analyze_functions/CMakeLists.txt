

set(__src
	FunctionScoreCalc.cpp
	MethodScore.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc_analyze_functions)

