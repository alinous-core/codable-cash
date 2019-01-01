
set(__dirsrc "")

# import source codes
add_subdirectory(bc_base)
add_subdirectory(bc_network)
add_subdirectory(flash)
add_subdirectory(main)

message(STATUS "src_blockchain : ${__dirsrc}")

set_parentv("${__dirsrc}" src_blockchain top_src_blockchain)

