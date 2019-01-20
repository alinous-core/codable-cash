
set(__src
	BigDecimal.cpp
	BigInteger.cpp
)
handle_sub(codablecashlib "${__src}" db numeric)
