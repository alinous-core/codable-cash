set(__src
	Character.cpp
	Exception.cpp
	exceptions.cpp
	Integer.cpp
	RawBitSet.cpp
	UnicodeString.cpp
)
handle_sub(codablecashlib "${__src}" db base)

