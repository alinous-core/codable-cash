
set(__src
	BigDecimal.cpp
	BigInteger.cpp
	BitLevel.cpp
	Conversion.cpp
	Division.cpp
	Elementary.cpp
	exceptions.cpp
	Multiplication.cpp
)
handle_sub(codablecashlib "${__src}" db numeric)
