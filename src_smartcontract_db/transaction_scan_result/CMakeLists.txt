

set(__src
	ScanResultFieldMetadata.cpp
	ScanResultMetadata.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_scan_result)

