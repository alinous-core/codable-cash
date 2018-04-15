

# import source codes
add_subdirectory(base)
add_subdirectory(base_io)
add_subdirectory(charsets)

message (STATUS "db source codes ${dbbasesrc}")
message (STATUS "db source codes ${dbiosrc}")
message (STATUS "db source codes ${dbcharsetssrc}")

add_library(alinousdb STATIC alinousdbmain.cpp ${dbbasesrc} ${dbiosrc} ${dbcharsetssrc})
target_link_libraries(alinousdb extlib pthread)



