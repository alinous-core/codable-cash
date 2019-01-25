/*
 * test_pow.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */


#include "numeric/BigInteger.h"
#include "base/StackRelease.h"
#include "base_io/ByteBuffer.h"
#include "flash_pow/NonceCalc.h"
#include "test_utils/t_macros.h"
#include "osenv/funcs.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestPoW) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestPoW, calc){
	NonceCalc calc;

	const char* passwd = "passwordpasswordpasswordpasswordpasswordpasswordpasswordpassword";

	ByteBuffer* in = ByteBuffer::wrap(passwd, 8*8);	__STP(in);
	ByteBuffer* nonce = ByteBuffer::wrap(passwd, 8);__STP(nonce);

	ByteBuffer* ans = calc.calc(in, nonce);__STP(ans);
}

TEST(TestPoW, calchash){
	NonceCalc calc;
	const char* passwd = "passwordpasswordpasswordpassword";
	ByteBuffer* in = ByteBuffer::wrap(passwd, 8*4);	__STP(in);
	ByteBuffer* nonce = ByteBuffer::wrap(passwd, 8*4);__STP(nonce);

	uint64_t tm1 =  Os::getMicroSec();

	int maxLoop = 10;
	for(int i = 0; i != maxLoop; ++i){
		ByteBuffer* ans = calc.calc(in, nonce);__STP(ans);
	}

	uint64_t tm2 = Os::getMicroSec();

	uint64_t tm = tm2 - tm1;
	double rate = maxLoop / (double)tm * 1000000;

	//::printf("rate : %lf\n", rate);


	BigInteger brate((int64_t)rate);
	calc.calcNecessaryDifficulty(brate, 10);

	//::printf("diff : %s\n", diff.toString(16).toCString());

	//calc.calcHash4Diff(diff);
	//BigInteger hash = calc.calcHash4Diff(diff);
	//::printf("hash : %s\n", hash.toString(16).toCString());
}


TEST(TestPoW, calcnoncehash){
	NonceCalc calc;

	BigInteger brate((int64_t)100);
	BigInteger diff = calc.calcNecessaryDifficulty(brate, 5);
	// ::printf("diff : %s\n", diff.toString(16).toCString());

	BigInteger hash = calc.calcHash4Diff(diff);
	UnicodeString out = hash.toString("%064Zx");
	//::printf("hash : %s\n", out.toCString());

	CHECK(out.startsWith(UnicodeString(L"00")))
}
