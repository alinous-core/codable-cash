

set(__src
	ConditionsHolder.cpp
	ConditionsHolderStack.cpp
	ConditionsHolderStackMarker.cpp
	SelectScanPlanner.cpp
	TablesHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner)

