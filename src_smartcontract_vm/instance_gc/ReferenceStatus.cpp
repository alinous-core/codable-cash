/*
 * ReferenceStatus.cpp
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#include "instance_gc/ReferenceStatus.h"
#include "instance_gc/GcManager.h"
#include "instance_gc/GcCyclicCheckerContext.h"

#include "instance_ref/AbstractReference.h"
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

	const IAbstractVmInstanceSubstance* o = list->search(owner);
	if(o == nullptr){
		list->addElementWithSorted(owner);
	}
}

void ReferenceStatus::removeOwner(const IAbstractVmInstanceSubstance* owner) noexcept {
	uint8_t type = owner->getInstType();
	ArrayList<const AbstractVmInstance>* list = nullptr;

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


bool ReferenceStatus::isRemovable() const noexcept {
	return this->ownerList.isEmpty() && this->terminalOwnerList.isEmpty();
}

void ReferenceStatus::releseInnerRefs(GcManager* gc) noexcept {
	IInstanceContainer* container = dynamic_cast<IInstanceContainer*>(this->instance);
	if(container != nullptr){
		((IInstanceContainer*)container)->removeInnerRefs(gc);
	}
}


IAbstractVmInstanceSubstance* ReferenceStatus::getInstance() const noexcept {
	return this->instance;
}

void ReferenceStatus::removeInstance() noexcept {
	if(this->instance != nullptr){
		delete this->instance;
	}
}

bool ReferenceStatus::checkCyclicRemovable(GcCyclicCheckerContext* cctx) noexcept {
	bool alreadyDone = cctx->hasStatus(this);
	if(alreadyDone){
		return true;
	}
	if(!this->terminalOwnerList.isEmpty()){
		return false;
	}

	cctx->addInstance(this);

	int maxLoop = this->ownerList.size();
	for(int i = 0; i != maxLoop; ++i){
		const AbstractVmInstance* inst = this->ownerList.get(i);

		bool result = checkInnerCyclicRemovable(inst, cctx);
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

bool ReferenceStatus::checkInnerCyclicRemovable(const AbstractVmInstance* inst, GcCyclicCheckerContext* cctx) const noexcept{
	const VMemList<AbstractReference>* list = inst->getReferences();
	if(list == nullptr){
		return true;
	}

	GcManager* gc = cctx->getGC();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractReference* ref = list->get(i);
		ReferenceStatus* stat = gc->getReferenceStatus(ref);

		bool result = stat->checkCyclicRemovable(cctx);
		if(!result){
			return false;
		}
	}

	return true;
}


} /* namespace alinous */
