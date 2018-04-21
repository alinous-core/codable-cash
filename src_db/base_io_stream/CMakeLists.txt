set(__src
	FileOutputStream.cpp
	InputStream.cpp
	OutputStream.cpp
)
handle_sub(codablecashlib "${__src}" db base_io_stream)


