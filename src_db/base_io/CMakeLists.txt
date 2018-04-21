set(__src
	ByteBuffer.cpp
	CharBuffer.cpp
	exceptions.cpp
	File.cpp
)
handle_sub("${__src}" db base_io)
