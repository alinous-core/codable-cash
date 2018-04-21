

set(__testsrc "")

# import source codes
add_subdirectory(base)
add_subdirectory(base_io)
add_subdirectory(base_io_stream)
add_subdirectory(base_thread)
add_subdirectory(charsets)
add_subdirectory(osenv)


message("-- src_db : ${__testsrc}")

set_parentv("${__testsrc}" src_db top_src_db)

