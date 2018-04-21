
set(__src
	CharsetManager.cpp
	CharsetConverter.cpp
	CharsetDecoder.cpp
	CharsetEncoder.cpp
	CoderResult.cpp
	UTF8.cpp
)
handle_sub(codablecashlib "${__src}" db charsets)

