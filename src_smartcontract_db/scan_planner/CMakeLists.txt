

set(__src
	ConditionsHolder.cpp
	SelectScanPlanner.cpp	
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner)

