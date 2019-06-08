/*
 * GcManager.cpp
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#include "instance_gc/GcManager.h"

#include "instance/AbstractVmInstance.h"

namespace alinous {

GcManager::GcManager() {
	this->mainInst = nullptr;

}

GcManager::~GcManager() {
	delete this->mainInst;
}

void GcManager::addReference(AbstractVmInstance* owner, AbstractVmInstance* refered) noexcept {
	// FIXME
}

void GcManager::removeReference(AbstractVmInstance* owner, AbstractVmInstance* refered) noexcept {
	// FIXME
}

} /* namespace alinous */
