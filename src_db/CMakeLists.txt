

# import source codes
add_subdirectory(base)

message (STATUS "ext source codes ${dbbasesrc}")

add_library(alinousdb STATIC alinousdbmain.cpp ${dbbasesrc})
target_link_libraries(alinousdb pthread)


