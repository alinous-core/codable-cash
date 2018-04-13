

# import source codes
add_subdirectory(base)
add_subdirectory(base_io)

message (STATUS "db source codes ${dbbasesrc}")
message (STATUS "db source codes ${dbiosrc}")


add_library(alinousdb STATIC alinousdbmain.cpp ${dbbasesrc} ${dbiosrc})
target_link_libraries(alinousdb pthread)


