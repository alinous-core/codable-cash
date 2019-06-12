

set(__src
	AnalyzeContext.cpp
	AnalyzedClass.cpp
	AnalyzedStackReference.cpp
	AnalyzedType.cpp
	AnalyzeStack.cpp
	AnalyzeStackManager.cpp
	PackageSpace.cpp
	ValidationError.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc_analyze)

