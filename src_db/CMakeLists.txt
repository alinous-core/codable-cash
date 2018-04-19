

# import source codes
add_subdirectory(base)
add_subdirectory(base_io)
add_subdirectory(base_io_stream)
add_subdirectory(charsets)
add_subdirectory(osenv)

set(__testsrc "")
list(APPEND __testsrc ${dbbasesrc})
list(APPEND __testsrc ${dbiosrc})
list(APPEND __testsrc ${dbiostreamsrc})
list(APPEND __testsrc ${dbcharsetssrc})
list(APPEND __testsrc ${osenvsrc})

set_parentv("${__testsrc}" src_db top_src_db)




