
set(__src
	DiskCacheManager.cpp
	MMapSegment.cpp
	MMapSegments.cpp
	RandomAccessFile.cpp
)
handle_sub(codablecashlib "${__src}" db random_access_file)
