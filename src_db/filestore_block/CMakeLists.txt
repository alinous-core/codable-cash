
set(__src
	BlockFileBody.cpp
	BlockFileHeader.cpp
	BlockFileStore.cpp
	exceptions.cpp
)
handle_sub(codablecashlib "${__src}" db filestore_block)
