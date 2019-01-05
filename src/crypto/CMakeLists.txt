

set(__src
	Schnorr.cpp
	SchnorrKeyPair.cpp
	SchnorrSignature.cpp
	Sha256.cpp
)

handle_sub(codablecashlib "${__src}" null crypto)


