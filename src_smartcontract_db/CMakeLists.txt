
set(__dirsrc "")

# import source codes
add_subdirectory(engine)
add_subdirectory(scan)
add_subdirectory(scan_condition)
add_subdirectory(scan_condition_arithmetic)
add_subdirectory(scan_condition_exp)
add_subdirectory(scan_condition_logical)
add_subdirectory(scan_condition_params)
add_subdirectory(scan_planner)
add_subdirectory(schema)
add_subdirectory(table)
add_subdirectory(table_record)
add_subdirectory(table_record_key)
add_subdirectory(table_record_value)
add_subdirectory(table_store)
add_subdirectory(transaction)
add_subdirectory(transaction_exception)
add_subdirectory(transaction_log)
add_subdirectory(transaction_scan_result)
add_subdirectory(transaction_scanner)
add_subdirectory(transaction_update_cache)

message(STATUS "src_smartcontract_db : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract_db top_src_smartcontract_db)
