

set(__dirsrc "")

# import source codes
add_subdirectory(base)
add_subdirectory(base_io)
add_subdirectory(base_io_stream)
add_subdirectory(base_thread)
add_subdirectory(btree)
add_subdirectory(btreekey)
add_subdirectory(charsets)
add_subdirectory(debug)
add_subdirectory(filestore)
add_subdirectory(filestore_block)
add_subdirectory(numeric)
add_subdirectory(osenv)
add_subdirectory(random_access_file)


message(STATUS "src_db : ${__dirsrc}")

set_parentv("${__dirsrc}" src_db top_src_db)

