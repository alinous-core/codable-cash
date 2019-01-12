/*
 * ConcurrentGate.cpp
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#include "base_thread/ConcurrentGate.h"
#include "base_thread/StackUnlocker.h"

namespace alinous {

ConcurrentGate::ConcurrentGate() noexcept {
	this->isOpened = true;
	this->counter = 0;
	this->roomWaiter = 0;
}

ConcurrentGate::~ConcurrentGate() {
}

void ConcurrentGate::enter() noexcept {
	{
		StackUnlocker __st_lock(&this->stateLock);
		if(this->isOpened){
			this->counter++;
		}
		else{
			{
				StackUnlocker __st_lock2(&this->roomLock);
				this->roomWaiter++;
			}
			this->stateLock.wait();
			/* ---------------------
						ROOM
			 ---------------------- */
			{
				StackUnlocker __st_lock2(&this->roomLock);

				this->roomWaiter--;
				if(this->roomWaiter == 0){
					this->roomLock.notify();
				}
			}
			this->counter++;
		}
	}
}

void ConcurrentGate::exit() noexcept {
	{
		StackUnlocker __st_lock(&this->stateLock);
		this->counter--;
		if(this->counter == 0){
			this->stateLock.notify();
		}
	}
}

void ConcurrentGate::open() noexcept {
	{
		StackUnlocker __st_lock(&this->stateLock);

		this->isOpened = true;
		this->stateLock.notify();
	}

	{
		StackUnlocker __st_lock(&this->roomLock);

		if(this->roomWaiter > 0){
			this->roomLock.wait();
		}
	}

	this->doorKeeperLock.unlock();
}

void ConcurrentGate::close() noexcept {
	this->doorKeeperLock.lock();

	{
		StackUnlocker __st_lock(&this->stateLock);

		this->isOpened = false; // close the gate
		if(this->counter > 0){
			//out(" [ Gate :" + Thread.currentThread().getId() + "] wait for reader threads ends");
			this->stateLock.wait();
		}
	}
}

} /* namespace alinous */
