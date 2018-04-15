
set(CMAKE_CXX_FLAGS "-std=c++0x -D__cplusplus=201103L -Wall -fmessage-length=0 -O3 -march=native")

# import source codes
add_subdirectory(yescrypt)
add_subdirectory(unicode)

message (STATUS "ext source codes ${yescryptsrc}")
message (STATUS "ext source codes ${unicodesrc}")

add_library(extlib STATIC extmain.cpp ${yescryptsrc} ${unicodesrc})
target_link_libraries(extlib pthread gmp)


