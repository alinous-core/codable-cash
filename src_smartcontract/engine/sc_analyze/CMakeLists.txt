

set(__src
	AnalyzeContext.cpp
	AnalyzedClass.cpp
	AnalyzedThisClassStackPopper.cpp
	AnalyzedType.cpp
	IVmInstanceFactory.cpp
	NameSegments.cpp
	PackageSpace.cpp
	TypeResolver.cpp
	ValidationError.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract engine/sc_analyze)

