
set(__testsrc "")

add_subdirectory(crypto)
add_subdirectory(db_base)
add_subdirectory(db_base_io)
add_subdirectory(db_base_io_stream)
add_subdirectory(db_charsets)
add_subdirectory(test_utils)

list(APPEND __testsrc ${cryptotestsrc})
#list(APPEND __testsrc ${db_base_test_src})
#list(APPEND __testsrc ${db_base_io_test_src})
#list(APPEND __testsrc ${test_base_io_stream_src})
#list(APPEND __testsrc ${db_charset_test_src})
#list(APPEND __testsrc ${test_utils_test_src})

message("-- src_test : ${__testsrc}")


set_parentv("${__testsrc}" src_test top_testsrc)



