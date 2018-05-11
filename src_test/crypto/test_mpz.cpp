#include <iostream>
#include <gmp.h>

#include "test_utils/t_macros.h"

using namespace alinous;

TEST_GROUP(MpzTestGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(MpzTestGroup, test01){
	mpz_t a, b;

	mpz_init(a);
	mpz_init_set_str(b ,"1234567890",10);

	mpz_mul(a, b, b);

	int count = 0;
	for(int i = 0; i != 1000000; ++i){
		mpz_set_str(b, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798", 16);
		mpz_mul(a, b, b);
		mpz_sqrt(b, a);
		count++;
	}

	mpz_set(a, b);

	mpz_clear(a);
	mpz_clear(b);
}

