/*
 * GcManager.cpp
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#include "instance/instance_gc/GcManager.h"

#include "instance/AbstractVmInstance.h"

#include "instance/instance_gc/ReferenceStatus.h"
#include "instance/instance_gc/VmInstanceKey.h"
#include "instance/instance_gc/GcCyclicCheckerContext.h"

#include "instance/instance_ref/AbstractReference.h"
#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/IAbstractVmInstanceSubstance.h"

#include "base/StackRelease.h"
#include <cassert>

#include "instance/IInstanceContainer.h"


namespace alinous {

GcManager::GcManager() {

}

GcManager::~GcManager() {
	//this->removable.deleteElements();
}

void GcManager::registerObject(AbstractReference* ref) {
	if(ref->isPrimitive() || ref->isNull()){
		return;
	}
	IAbstractVmInstanceSubstance* refered = ref->getInstance();
	IAbstractVmInstanceSubstance* owner = ref->getOwner();

	VmInstanceKey key(refered);

	bool newObj = false;
	int lastOwnerSize = 0;
	ReferenceStatus* status = this->statuses.get(&key);

	if(status == nullptr){
		status = new ReferenceStatus(refered);
		this->statuses.put(&key, status);
		newObj = true;
	}
	else{
		lastOwnerSize = status->ownerSize();
	}

	status->addOwner(owner);

	// remove from removeble
	if(!newObj && lastOwnerSize == 0){
		removeFromRemoveble(status);
	}
}

void GcManager::removeObject(AbstractReference* ref) {
	if(ref->isPrimitive() || ref->isNull()){
		return;
	}

	IAbstractVmInstanceSubstance* refered = ref->getInstance();

	VmInstanceKey key(refered);

	ReferenceStatus* status = this->statuses.get(&key);
	assert(status != nullptr);

	IAbstractVmInstanceSubstance* owner = ref->getOwner();
	status->removeOwner(owner);

	if(status->isRemovable()){
		addToRemoveble(status);
	}
	else{
		addToNeedCheck(status);
	}
}

void GcManager::addToRemoveble(ReferenceStatus* status) noexcept {
	ReferenceStatus* stat = this->removable.search(status);

	if(stat == nullptr){
		this->removable.addElementWithSorted(status);
		removeFromNeedCheck(status);
	}
}


void GcManager::addToNeedCheck(ReferenceStatus* status) noexcept {
	VmInstanceKey key(status->getInstance());

	ReferenceStatus* rstatus = this->needCheck.get(&key);
	if(rstatus == nullptr){
		this->needCheck.put(&key, status);
	}
}

void GcManager::removeFromNeedCheck(ReferenceStatus* status) noexcept {
	VmInstanceKey key(status->getInstance());

	this->needCheck.remove(&key);
}

void GcManager::removeFromRemoveble(ReferenceStatus* status) noexcept {
	ReferenceStatus* st = this->removable.search(status);

	if(st != nullptr){
		this->removable.removeByObj(status);
	}
}

void GcManager::garbageCollect() {
	while(!this->removable.isEmpty() || !this->needCheck.isEmpty()){
		while(!this->removable.isEmpty()){
			ReferenceStatus* status = this->removable.remove(0);
			VmInstanceKey key(status->getInstance());

			this->statuses.remove(&key);
			this->needCheck.remove(&key);

			status->releseInnerRefs(this);
			status->deleteInstance();

			delete status;
		}

		checkCycric();
	}
}

ReferenceStatus* GcManager::getReferenceStatus(const IAbstractVmInstanceSubstance* ref) const noexcept {
	VmInstanceKey key(ref);
	ReferenceStatus* status = this->statuses.get(&key);

	return status;
}


void GcManager::checkCycric() noexcept {
	HashMap<VmInstanceKey, ReferenceStatus> checkHash;
	copyAll(&checkHash);

	ArrayList<GcCyclicCheckerContext> list;
	list.setDeleteOnExit();

	Iterator<VmInstanceKey>* it = checkHash.keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const VmInstanceKey* key = it->next();
		ReferenceStatus* status = checkHash.get(key);

		GcCyclicCheckerContext* context = new GcCyclicCheckerContext(this);

		bool result = status->checkCyclicRemovable(context, this);
		if(!result){
			delete context;
			removeFromNeedCheck(status);
			continue;
		}

		list.addElement(context);
		removeFromNeedCheck(status);
	}

	int maxLoop = list.size();
	for(int i = 0; i != maxLoop; ++i){
		GcCyclicCheckerContext* context = list.get(i);
		removeGcCyclicCheckerContext(context);
	}
}

void GcManager::removeGcCyclicCheckerContext(GcCyclicCheckerContext* cctx) noexcept {
	const ArrayList<ReferenceStatus>* list = cctx->getOwnerList();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		ReferenceStatus* stat = list->get(i);

		stat->releseInnerRefs(this);
	}
}

void GcManager::copyAll(HashMap<VmInstanceKey, ReferenceStatus>* checkHash) noexcept {
	Iterator<VmInstanceKey>* it = this->needCheck.keySet()->iterator(); __STP(it);

	while(it->hasNext()){
		const VmInstanceKey* key = it->next();
		ReferenceStatus* status = this->needCheck.get(key);

		checkHash->put(key, status);
	}
}

void GcManager::handleFloatingObject(IAbstractVmInstanceSubstance* refered) noexcept {
	if(refered == nullptr){
		return;
	}
	else if(refered->instIsPrimitive()){
		PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(refered);

		if(!ref->isStaticConst() && ref->getOwner() == nullptr){
			delete refered;
		}
		return;
	}

	VmInstanceKey key(refered);
	ReferenceStatus* status = this->statuses.get(&key);
	if(status != nullptr){
		return;
	}

	IInstanceContainer* container = dynamic_cast<IInstanceContainer*>(refered);
	if(container != nullptr){
		container->removeInnerRefs(this);
	}


	delete refered;
}

bool GcManager::isEmpty() const noexcept {
	return this->statuses.isEmpty();
}


} /* namespace alinous */
