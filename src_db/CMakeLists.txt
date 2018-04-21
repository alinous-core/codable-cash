

set(__dirsrc "")

# import source codes
add_subdirectory(base)
add_subdirectory(base_io)
add_subdirectory(base_io_stream)
add_subdirectory(base_thread)
add_subdirectory(charsets)
add_subdirectory(osenv)


message("-- src_db : ${__dirsrc}")

set_parentv("${__dirsrc}" src_db top_src_db)

