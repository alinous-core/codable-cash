/*
 * GateTester.cpp
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#include "db/db_base_thread/GateTester.h"
#include "db/db_base_thread/CriticalSectionMarkerException.h"
#include "db/db_base_thread/CriticalSectionMarker.h"

#include "base_thread/SysThread.h"
#include "base_thread/StackUnlocker.h"
#include "base_thread/ConcurrentGate.h"

namespace alinous {

SynchronizedLock* GateTester::launchComplete =  GateTester::getStaticLock();
Exception* GateTester::lastException = nullptr;
CriticalSectionMarker* GateTester::criticalMarker = GateTester::getMarker();


SynchronizedLock* GateTester::getStaticLock() noexcept {
	static SynchronizedLock lock;
	return &lock;
}

CriticalSectionMarker* GateTester::getMarker() noexcept {
	static CriticalSectionMarker inst;
	return &inst;
}

GateTester::GateTester() {
	this->mode = 0;
	this->startLock = nullptr;
	this->loops = 0;
	this->gate = nullptr;
	this->id = 0;
	this->ready = false;
}

GateTester::~GateTester() {
}

void GateTester::init(int mode, SynchronizedLock* startLock, int loops,	ConcurrentGate* gate) {
	this->mode = mode;
	this->startLock = startLock;
	this->loops = loops;
	this->gate = gate;
}

void GateTester::process() noexcept {
	THREAD_ID id = Os::getCurrentThreadId();

	{
		StackUnlocker __st_lock(this->startLock);
		{
			{
				StackUnlocker __st_lock2(GateTester::launchComplete);
				GateTester::launchComplete->notifyAll();
				this->ready = true;
			}

			this->startLock->wait();
		}
	}

	try{
		if(this->mode == GateTester::WRITER){
			writer();
		}else if(this->mode == GateTester::READER){
			reader();
		}
	}
	catch (CriticalSectionMarkerException* e) {
		GateTester::lastException = e;
	}
}

void GateTester::writer() {
	for (int i = 0; i < this->loops; i++) {
		this->gate->close();
		GateTester::criticalMarker->enter();

		//printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

		Os::usleep(3);

		GateTester::criticalMarker->exit();
		this->gate->open();
	}
}


void GateTester::reader() {
	for (int i = 0; i < this->loops; i++) {
		this->gate->enter();

		GateTester::criticalMarker->checkCritical();

		Os::usleep(1);

		/*printf("-------------------------\n");
		printf("-------------------------\n");
		printf("-------------------------\n");
		printf("-------------------------\n");*/

		this->gate->exit();
	}
}

} /* namespace alinous */
