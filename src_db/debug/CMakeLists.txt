
set(__src
	ErrorActivationPoint.cpp
	ErrorOccurrence.cpp
	ErrorPointManager.cpp
)
handle_sub(codablecashlib "${__src}" db debug)
