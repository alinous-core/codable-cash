/*
 * GcCyclicCheckerContext.cpp
 *
 *  Created on: 2019/07/17
 *      Author: iizuka
 */

#include "instance/instance_gc/GcCyclicCheckerContext.h"
#include "instance/AbstractVmInstance.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/ReferenceStatus.h"

namespace alinous {

GcCyclicCheckerContext::GcCyclicCheckerContext(GcManager* gc) {
	this->gc = gc;
}

GcCyclicCheckerContext::~GcCyclicCheckerContext() {

}

void GcCyclicCheckerContext::addInstance(ReferenceStatus* inst) noexcept {
	ReferenceStatus* stat = this->ownerList.search(inst);
	if(stat == nullptr){
		this->ownerList.addElementWithSorted(inst);
	}
}

bool GcCyclicCheckerContext::hasStatus(const ReferenceStatus* inst) noexcept {
	const ReferenceStatus* stat = this->ownerList.search(inst);
	return stat != nullptr;
}

/*GcManager* GcCyclicCheckerContext::getGC() const noexcept {
	return this->gc;
}*/

const ArrayList<ReferenceStatus>* alinous::GcCyclicCheckerContext::getOwnerList() const noexcept {
	return &this->ownerList;
}


} /* namespace alinous */
