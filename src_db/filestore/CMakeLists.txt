
set(__src
	exceptions.cpp
	FileStore.cpp
	LongRange.cpp
	LongRangeHitStatus.cpp
	LongRangeIterator.cpp
	LongRangeList.cpp
)
handle_sub(codablecashlib "${__src}" db filestore)
