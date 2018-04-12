


# import source codes
add_subdirectory(crypto)

message (STATUS "source codes  ${cryptosrc}")

add_library(codablelib STATIC libmain.cpp ${cryptosrc})
target_link_libraries(codablelib pthread gmp)



