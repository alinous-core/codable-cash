/*
 * SynchronizedLock.cpp
 *
 *  Created on: 2018/04/28
 *      Author: iizuka
 */

#include "base_thread/SynchronizedLock.h"

#include "debug/debugMacros.h"

namespace alinous {

SynchronizedLock::SynchronizedLock() : ILock() {
	this->cond = new LockCondition();
	::pthread_cond_init(&this->cond->cond, 0);
	::pthread_mutex_init(&mutex, NULL);
}

SynchronizedLock::~SynchronizedLock() {
	::pthread_cond_destroy(&this->cond->cond);
	::pthread_mutex_destroy(&mutex);
	delete this->cond;
}

void SynchronizedLock::lock() {
	::pthread_mutex_lock(&mutex);
}

void SynchronizedLock::unlock() {
	::pthread_mutex_unlock(&mutex) ;
}

void SynchronizedLock::wait() {
	::pthread_cond_wait(&this->cond->cond, &mutex);
}

void SynchronizedLock::notifyAll() {
	::pthread_cond_broadcast(&this->cond->cond);
}

} /* namespace alinous */
