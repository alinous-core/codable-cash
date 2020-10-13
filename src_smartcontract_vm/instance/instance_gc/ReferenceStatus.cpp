/*
 * ReferenceStatus.cpp
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#include "instance/instance_gc/ReferenceStatus.h"
#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/GcCyclicCheckerContext.h"

#include "instance/instance_ref/AbstractReference.h"
#include "instance/IInstanceContainer.h"
#include "instance/VmInstanceTypesConst.h"

namespace alinous {

ReferenceStatus::ReferenceStatus(IAbstractVmInstanceSubstance* instance) {
	this->instance = instance;
}

ReferenceStatus::~ReferenceStatus() {
	this->instance = nullptr;
}

void ReferenceStatus::addOwner(const IAbstractVmInstanceSubstance* owner) noexcept {
	uint8_t type = owner->getInstType();

	ArrayList<const IAbstractVmInstanceSubstance>* list = nullptr;

	switch(type){
	case VmInstanceTypesConst::STACK:
	case VmInstanceTypesConst::REF_ROOT:
		list = &this->terminalOwnerList;
		break;
	default:
		list = &this->ownerList;
		break;
	}

	//const IAbstractVmInstanceSubstance* o = list->search(owner);
	//if(o == nullptr){
	//	list->addElementWithSorted(owner);
	//}
	list->addElementWithSorted(owner);
}

void ReferenceStatus::removeOwner(const IAbstractVmInstanceSubstance* owner) noexcept {
	uint8_t type = owner->getInstType();
	ArrayList<const IAbstractVmInstanceSubstance>* list = nullptr;

	switch(type){
	case VmInstanceTypesConst::STACK:
	case VmInstanceTypesConst::REF_ROOT:
		list = &this->terminalOwnerList;
		break;
	default:
		list = &this->ownerList;
		break;
	}

	bool bl = list->removeByObj(owner);
	assert(bl);
}

int ReferenceStatus::ownerSize() const noexcept {
	return this->ownerList.size() + this->terminalOwnerList.size();
}


bool ReferenceStatus::isRemovable() const noexcept {
	return this->ownerList.isEmpty() && this->terminalOwnerList.isEmpty();
}

void ReferenceStatus::releseInnerRefs(GcManager* gc) noexcept {
	IInstanceContainer* container = dynamic_cast<IInstanceContainer*>(this->instance);
	if(container != nullptr){
		container->removeInnerRefs(gc);
	}
}


IAbstractVmInstanceSubstance* ReferenceStatus::getInstance() const noexcept {
	return this->instance;
}

bool ReferenceStatus::checkCyclicRemovable(GcCyclicCheckerContext* cctx, GcManager* gc) noexcept {
	if(!this->terminalOwnerList.isEmpty()){
		return false;
	}

	bool alreadyDone = cctx->hasStatus(this);
	if(alreadyDone){
		return true;
	}

	cctx->addInstance(this);

	int maxLoop = this->ownerList.size();
	for(int i = 0; i != maxLoop; ++i){
		const IAbstractVmInstanceSubstance* inst = this->ownerList.get(i);

		//bool result = checkInnerCyclicRemovable(inst, cctx);
		ReferenceStatus* stat = gc->getReferenceStatus(inst);
		bool result = stat->checkCyclicRemovable(cctx, gc);
		if(!result){
			return false;
		}
	}

	return true;
}

void ReferenceStatus::deleteInstance() noexcept {
	uint8_t type = this->instance->getInstType();

	//if(type == VmInstanceTypesConst::STACK){
	//	return;
	//}

	delete this->instance;
}


} /* namespace alinous */
