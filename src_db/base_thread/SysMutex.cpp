/*
 * SysMutex.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "SysMutex.h"

namespace alinous {

SysMutex::SysMutex() noexcept : ILock() {
	pthread_mutex_init(&mutex, nullptr);
	this->count = 0;
}

SysMutex::~SysMutex() noexcept {
	pthread_mutex_destroy(&mutex);
}

void SysMutex::lock() noexcept {
	pthread_mutex_lock(&mutex);
	this->count++;
}


void SysMutex::unlock() noexcept {
	this->count--;
	pthread_mutex_unlock(&mutex);
}


} /* namespace codablecash */
