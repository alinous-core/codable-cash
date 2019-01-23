

set(__src
	BlockchainsConfig.cpp
	CodablecashBlockchains.cpp
	exceptions.cpp
)
handle_sub(codablecashlib "${__src}" blockchain bc)

