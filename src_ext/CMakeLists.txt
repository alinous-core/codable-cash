
set(CMAKE_CXX_FLAGS "-std=c++0x -D__cplusplus=201103L -Wall -fmessage-length=0 -O3 -march=native")

# import source codes
add_subdirectory(yescrypt)

message (STATUS "ext source codes ${yescryptsrc}")

add_library(extlib STATIC extmain.cpp ${yescryptsrc})
target_link_libraries(extlib pthread gmp)


