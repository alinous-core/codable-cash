
set(__src
	BtreeKeyFactory.cpp
	exceptions.cpp
	InfinityKey.cpp
	NullKey.cpp
	ULongKey.cpp
)
handle_sub(codablecashlib "${__src}" db btreekey)
