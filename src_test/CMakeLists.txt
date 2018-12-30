
set(__dirsrc "")

add_subdirectory(blockchain)
add_subdirectory(crypto)
add_subdirectory(db_base)
add_subdirectory(db_base_io)
add_subdirectory(db_base_io_stream)
add_subdirectory(db_base_thread)
add_subdirectory(db_btree)
add_subdirectory(db_charsets)
add_subdirectory(db_filestore)
add_subdirectory(db_random_access_file)
add_subdirectory(smartcontract)
add_subdirectory(smartcontract_vm)
add_subdirectory(test_utils)

message("-- src_test : ${__dirsrc}")

set_parentv("${__dirsrc}" src_test top_testsrc)



