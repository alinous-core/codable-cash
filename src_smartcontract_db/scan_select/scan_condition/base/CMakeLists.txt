

set(__src
	AbstractScanCondition.cpp
	AbstractScanConditionElement.cpp
	IValueProvider.cpp
	RootScanCondition.cpp
	ScanConditionCast.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_condition/base)

