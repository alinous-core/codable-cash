
set(__src
	BTreeKeyFactory.cpp
	InfinityKey.cpp
	ULongKey.cpp
)
handle_sub(codablecashlib "${__src}" db btreekey)
