/*
 * GcManager.cpp
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#include "instance_gc/GcManager.h"

#include "instance/AbstractVmInstance.h"

#include "instance_gc/ReferenceStatus.h"
#include "instance_gc/VmInstanceKey.h"
#include "instance_gc/GcCyclicCheckerContext.h"

#include "instance_ref/AbstractReference.h"

#include "base/StackRelease.h"
#include <cassert>


namespace alinous {

GcManager::GcManager() {

}

GcManager::~GcManager() {
	//this->removable.deleteElements();
}

void GcManager::addInstanceReference(AbstractVmInstance* owner, AbstractVmInstance* refered) noexcept {
	VmInstanceKey key(refered);

	ReferenceStatus* status = this->statuses.get(&key);
	if(status == nullptr){
		status = new ReferenceStatus(refered);
		this->statuses.put(&key, status);
	}

	status->addOwner(owner);
}


void GcManager::removeInstanceReference(AbstractVmInstance* owner, AbstractVmInstance* refered) noexcept {
	VmInstanceKey key(refered);

	ReferenceStatus* status = this->statuses.get(&key);
	assert(status != nullptr);

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

void GcManager::garbageCollect() {
	while(!this->removable.isEmpty() || !this->needCheck.isEmpty()){
		while(!this->removable.isEmpty()){
			ReferenceStatus* status = this->removable.remove(0);
			status->releseInnerRefs(this);

			status->deleteInstance();

			delete status;
		}

		checkCycric();
	}
}

ReferenceStatus* GcManager::getReferenceStatus(AbstractReference* ref) const noexcept {
	VmInstanceKey key(ref->getInstance());
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
		ReferenceStatus* status = this->needCheck.get(key);

		GcCyclicCheckerContext* context = new GcCyclicCheckerContext(this);
		list.addElement(context);

		bool result = status->checkCyclicRemovable(context);
		if(!result){
			return;
		}
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
		addToRemoveble(stat);
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

void GcManager::handleFloatingObject(AbstractVmInstance* refered) noexcept {
	if(refered == nullptr){
		return;
	}

	VmInstanceKey key(refered);
	ReferenceStatus* status = this->statuses.get(&key);
	if(status != nullptr){
		return;
	}

	ReferenceStatus* needCheckStatus = this->needCheck.get(&key);
	if(needCheckStatus != nullptr){
		return;
	}

	ReferenceStatus tmp(refered);
	ReferenceStatus* removableStatus = this->removable.search(&tmp);
	if(removableStatus != nullptr){
		return;
	}

	delete refered;
}


} /* namespace alinous */
