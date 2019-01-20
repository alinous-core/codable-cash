/*
 * test_concurrent_gate.cpp
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_thread/ConcurrentGate.h"
#include "db/db_base_thread/GateTester.h"
#include "base/ArrayList.h"
#include "base_thread/StackUnlocker.h"

#include "osenv/funcs.h"

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

	SynchronizedLock myLock;
	ArrayList<GateTester> list;
	list.setDeleteOnExit();

	for(int i = 0; i < wthreads; i++){
		GateTester* tester = new GateTester();
		tester->init(GateTester::WRITER, &myLock, wloops, gate);
		tester->start();

		list.addElement(tester);

		{
			StackUnlocker __st_lock(GateTester::launchComplete);
			if(!tester->ready){
				GateTester::launchComplete->wait();
			}
		}
	}

	for(int i = 0; i < rthreads; i++){
		GateTester* tester = new GateTester();
		tester->init(GateTester::READER, &myLock, wloops, gate);
		tester->start();

		list.addElement(tester);

		{
			StackUnlocker __st_lock(GateTester::launchComplete);
			if(!tester->ready){
				GateTester::launchComplete->wait();
			}
		}
	}

	{
		StackUnlocker __st_lock(&myLock);
		myLock.notifyAll();
	}

	int maxLoop = list.size();
	for(int i = 0; i != maxLoop; ++i){
		GateTester* tester = list.get(i);
		tester->join();
	}

	CHECK(GateTester::lastException == nullptr);
}
