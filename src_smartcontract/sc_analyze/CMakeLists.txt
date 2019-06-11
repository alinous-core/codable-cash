

set(__src
	AnalyzeContext.cpp
	AnalyzedClass.cpp
	AnalyzedType.cpp
	PackageSpace.cpp
	ValidationError.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc_analyze)

