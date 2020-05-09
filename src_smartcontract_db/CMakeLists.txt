
set(__dirsrc "")

# import source codes
add_subdirectory(engine)
add_subdirectory(transaction)


message(STATUS "src_smartcontract_db : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract_db top_src_smartcontract_db)
