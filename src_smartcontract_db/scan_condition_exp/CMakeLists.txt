

set(__src
	EqualityScanCondition.cpp
	ParenthesisScanCondition.cpp
	RelationalScanCondition.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_condition_exp)

