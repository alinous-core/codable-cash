/*
 * GateTester.cpp
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#include "db_base_thread/GateTester.h"
#include "db_base_thread/CriticalSectionMarkerException.h"

#include "base_thread/SysThread.h"
#include "base_thread/StackUnlocker.h"
namespace alinous {

SynchronizedLock* GateTester::launchComplete = new SynchronizedLock();
Exception* GateTester::lastException = nullptr;

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
			}

			this->ready = true;
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
}

void GateTester::reader() {
}

} /* namespace alinous */
