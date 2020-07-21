

set(__src
	ConditionsHolder.cpp
	ConditionStackPopper.cpp
	SelectScanPlanner.cpp	
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner)

