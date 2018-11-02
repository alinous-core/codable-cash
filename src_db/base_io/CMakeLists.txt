set(__src
	ByteBuffer.cpp
	CharBuffer.cpp
	exceptions.cpp
	File.cpp
	ReverseByteBuffer.cpp
)
handle_sub(codablecashlib "${__src}" db base_io)
