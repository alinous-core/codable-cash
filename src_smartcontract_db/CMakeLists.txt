
set(__dirsrc "")

# import source codes
add_subdirectory(engine)
add_subdirectory(schema)
add_subdirectory(table)
add_subdirectory(transaction)
add_subdirectory(transaction_log)

message(STATUS "src_smartcontract_db : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract_db top_src_smartcontract_db)
