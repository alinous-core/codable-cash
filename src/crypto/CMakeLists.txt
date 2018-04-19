

set(__src
	Schnorr.cpp
	SchnorrKeyPair.cpp
	SchnorrSignature.cpp
)
set_parentv("${__src}" crypto cryptosrc)

outgcov(report_crypto ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src/crypto "${__src}")


