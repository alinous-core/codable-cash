
set(__src
	BigDecimal.cpp
	BigInteger.cpp
	BitLevel.cpp
	Conversion.cpp
	Elementary.cpp
	Multiplication.cpp
)
handle_sub(codablecashlib "${__src}" db numeric)
