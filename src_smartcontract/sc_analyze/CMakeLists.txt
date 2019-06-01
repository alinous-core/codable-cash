

set(__src
	AnalyzeContext.cpp
	AnalyzedClass.cpp
	PackageSpace.cpp
	ValidationError.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc_analyze)

