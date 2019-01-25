

set(__src
	IKeyPair.cpp
	Schnorr.cpp
	SchnorrKeyPair.cpp
	SchnorrSignature.cpp
	Sha256.cpp
)

handle_sub(codablecashlib "${__src}" null crypto)


