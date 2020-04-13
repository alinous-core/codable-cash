

set(__src
	AnalyzeContext.cpp
	AnalyzedClass.cpp
	AnalyzedThisClassStackPopper.cpp
	AnalyzedType.cpp
	IVmInstanceFactory.cpp
	PackageSpace.cpp
	TypeResolver.cpp
	ValidationError.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc_analyze)

