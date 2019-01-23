
set(__src
	BigDecimal.cpp
	BigInteger.cpp
	exceptions.cpp
	Multiplication.cpp
)
handle_sub(codablecashlib "${__src}" db numeric)
