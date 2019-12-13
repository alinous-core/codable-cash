

set(__src
	FunctionScoreCalc.cpp
	MethodNameCollection.cpp
	MethodScore.cpp
	VTableClassEntry.cpp
	VTableMethodEntry.cpp
	VTableRegistory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc_analyze_functions)

