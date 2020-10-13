

set(__src
	AndScanCondition.cpp
	NotScanCondition.cpp
	OrScanCondition.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_condition_logical)

