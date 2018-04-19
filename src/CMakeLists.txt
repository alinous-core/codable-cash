
# import source codes
add_subdirectory(crypto)


set(__src "")
list(APPEND __src ${cryptosrc})

set_parentv("${__src}" src top_src)


