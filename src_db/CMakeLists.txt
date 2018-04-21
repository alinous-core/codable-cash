

set(__testsrc "")

# import source codes
add_subdirectory(base)
add_subdirectory(base_io)
add_subdirectory(base_io_stream)
add_subdirectory(base_thread)
add_subdirectory(charsets)
add_subdirectory(osenv)


#list(APPEND __testsrc ${db_base_src})
#list(APPEND __testsrc ${dbiosrc})
#list(APPEND __testsrc ${dbiostreamsrc})
##list(APPEND __testsrc ${db_base_thread_src})
#list(APPEND __testsrc ${dbcharsetssrc})
list(APPEND __testsrc ${osenvsrc})

message("############ ${__testsrc}")

set_parentv("${__testsrc}" src_db top_src_db)




