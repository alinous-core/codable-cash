

set(__src
	BetweenScanCondition.cpp
	EqualityScanCondition.cpp
	IsNullScanCondition.cpp
	ParenthesisScanCondition.cpp
	RelationalScanCondition.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_condition_exp)

