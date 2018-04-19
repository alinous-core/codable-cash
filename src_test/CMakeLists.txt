
add_subdirectory(crypto)
add_subdirectory(db_base)
add_subdirectory(db_base_io)
add_subdirectory(db_charsets)


list(APPEND __testsrc ${cryptotestsrc})
list(APPEND __testsrc ${db_base_test_src})
list(APPEND __testsrc ${db_base_io_test_src})
list(APPEND __testsrc ${db_charset_test_src})


set_parentv("${__testsrc}" src_test top_testsrc)



