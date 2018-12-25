
set(__src
	BTreeKeyFactory.cpp
	exceptions.cpp
	InfinityKey.cpp
	ULongKey.cpp
)
handle_sub(codablecashlib "${__src}" db btreekey)
