
set(__src
	BlockData.cpp
	BlockFileBody.cpp
	BlockFileHeader.cpp
	BlockFileStore.cpp
	BlockHandle.cpp
	exceptions.cpp
)
handle_sub(codablecashlib "${__src}" db filestore_block)
