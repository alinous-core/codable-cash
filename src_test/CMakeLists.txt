
set(__dirsrc "")

add_subdirectory(crypto)
add_subdirectory(db_base)
add_subdirectory(db_base_io)
add_subdirectory(db_base_io_stream)
add_subdirectory(db_charsets)
add_subdirectory(test_utils)

message("-- src_test : ${__dirsrc}")

set_parentv("${__dirsrc}" src_test top_testsrc)



