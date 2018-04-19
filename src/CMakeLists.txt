


# import source codes
add_subdirectory(crypto)

message (STATUS "source codes  ${cryptosrc}")

set(__testsrc "")
list(APPEND __testsrc ${cryptosrc})

set_parentv("${__testsrc}" src top_src)


#[[
add_library(codablelib STATIC libmain.cpp ${cryptosrc})
target_link_libraries(codablelib pthread gmp)
]]#


