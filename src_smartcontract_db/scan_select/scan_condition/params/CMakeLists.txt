

set(__src
	AbstractScanConditionParameter.cpp
	BooleanScanParam.cpp
	ColumnIdentifierScanParam.cpp
	MultipleValueProvidorScanParam.cpp
	NumericScanParam.cpp
	PlaceHolderScanCondition.cpp
	StringScanParam.cpp
	WildCardScanParam.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_condition/params)

