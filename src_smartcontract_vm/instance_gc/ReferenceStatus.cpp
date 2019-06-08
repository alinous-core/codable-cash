/*
 * ReferenceStatus.cpp
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#include "instance_gc/ReferenceStatus.h"

namespace alinous {

ReferenceStatus::ReferenceStatus(AbstractVmInstance* instance) {
	this->instance = instance;
}

ReferenceStatus::~ReferenceStatus() {
	this->instance = nullptr;
}


} /* namespace alinous */
