set(__src
	exceptions.cpp
	FileInputStream.cpp
	FileOutputStream.cpp
	InputStream.cpp
	InputStreamReader.cpp
	OutputStream.cpp
	OutputStreamWriter.cpp
	Reader.cpp
	Writer.cpp
)
handle_sub(codablecashlib "${__src}" db base_io_stream)


