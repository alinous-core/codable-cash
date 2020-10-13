

set(__src
	AnalyzedStackReference.cpp
	AnalyzeStack.cpp
	AnalyzeStackManager.cpp
	AnalyzeStackPopper.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract engine/sc_analyze_stack)

