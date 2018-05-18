
set(__src
	exceptions.cpp
	FileStore.cpp
)
handle_sub(codablecashlib "${__src}" db filestore)
