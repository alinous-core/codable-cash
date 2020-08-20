

set(__src
	AbstractColumnParam.cpp
	NumberLiteralColumnParam.cpp
	StringLiteralColumnParam.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns_params)

