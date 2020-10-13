

set(__src
	AnalyzedScanPlan.cpp
	ScanColumnNameResolver.cpp
	ScanTargetNameResolver.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_planner/analyze)

