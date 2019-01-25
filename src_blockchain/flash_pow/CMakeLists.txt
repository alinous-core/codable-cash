

set(__src
	Nonce.cpp
	NonceCalc.cpp
)
handle_sub(codablecashlib "${__src}" blockchain flash_pow)

