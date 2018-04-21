

set(__src
	Schnorr.cpp
	SchnorrKeyPair.cpp
	SchnorrSignature.cpp
)

handle_sub(codablecashlib "${__src}" null crypto)


