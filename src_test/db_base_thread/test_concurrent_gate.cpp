/*
 * test_concurrent_gate.cpp
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_thread/ConcurrentGate.h"

using namespace alinous;

TEST_GROUP(ConccurentGateTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(ConccurentGateTestGroup, run){
	int rloops = 100;
	int wloops = 200;
	//int uloops = 20;

	int rthreads = 100;
	int wthreads = 40;
	//int uthreads = 1;

	ConcurrentGate* gate = new ConcurrentGate();
	StackRelease<ConcurrentGate> __st_gate(gate);

}
