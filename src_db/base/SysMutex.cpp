/*
 * SysMutex.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "SysMutex.h"

namespace alinous {

SysMutex::SysMutex() noexcept {
	pthread_mutex_init(&mutex, nullptr);
}

SysMutex::~SysMutex() noexcept {
	pthread_mutex_destroy(&mutex);
}

void SysMutex::lock() noexcept {
	pthread_mutex_lock(&mutex);
}


void SysMutex::unlock() noexcept {
	pthread_mutex_unlock(&mutex);
}


} /* namespace codablecash */
