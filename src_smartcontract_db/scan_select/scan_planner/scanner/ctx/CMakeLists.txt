

set(__src
	FilterConditionDitector.cpp
	FilterConditionStack.cpp
	FilterConditionStackMarker.cpp
	ScanJoinContext.cpp
	ScanJoinContextHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_planner/scanner/ctx)

