

set(__dirsrc "")

# import source codes
add_subdirectory(alinous_lang)



message(STATUS "src_gen : ${__dirsrc}")

set_parentv("${__dirsrc}" src_gen top_src_gen)

