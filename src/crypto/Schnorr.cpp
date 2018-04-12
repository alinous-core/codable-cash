/*
 * Schnorr.cpp
 *
 *  Created on: 2018/04/12
 *      Author: iizuka
 */

#include "Schnorr.h"


namespace codablecash {



SchnorrConsts::SchnorrConsts(){
	mpz_init_set_str(this->Q, "ff66c4652cbb54e13e4cc75898014aef72332e147343a95031cf416ca9f77ce7", 16);
	mpz_init_set_str(this->Q_1, "ff66c4652cbb54e13e4cc75898014aef72332e147343a95031cf416ca9f77ce6", 16);
	mpz_init_set_str(this->G, "e000000000000000000000000000000000000000000000000000000000000002", 16);
}
SchnorrConsts::~SchnorrConsts(){
	mpz_clear(this->Q);
	mpz_clear(this->Q_1);
	mpz_clear(this->G);
}

SchnorrConsts Schnorr::cnsts;

Schnorr::Schnorr() {
}

Schnorr::~Schnorr() {
}

SchnorrKeyPair* Schnorr::generateKey(){
	mpz_t s, p;
	mpz_init(s);
	mpz_init(p);

	gmp_randstate_t state;
	gmp_randinit_default(state);

	mpz_urandomb (s, state, 256);

	mpz_powm(p, cnsts.G, s, cnsts.Q);

	SchnorrKeyPair* pair = new SchnorrKeyPair(s, p);

	gmp_randclear(state);
	mpz_clear(s);
	mpz_clear(p);

	return pair;
}

}


