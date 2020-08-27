

set(__src
	AnalyzedScanPlan.cpp
	ScanTargetNameResolver.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner_analyze)

