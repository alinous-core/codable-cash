/*
 * NodeCacheRef.cpp
 *
 *  Created on: 2018/12/24
 *      Author: iizuka
 */

#include "btree_cache/NodeCacheRef.h"

#include "btree/AbstractTreeNode.h"

namespace alinous {

NodeCacheRef::NodeCacheRef(AbstractTreeNode* node, SynchronizedLock* parentLock) {
	this->count = 0;
	this->node = node;
	this->parentLock = parentLock;
}

NodeCacheRef::~NodeCacheRef() {
	delete this->node;
}

void NodeCacheRef::inc() {
	this->lock.lock();
	this->count++;
	this->lock.unlock();
}

void NodeCacheRef::dec() {
	this->parentLock->lock();

	this->lock.lock();
	this->count--;

	if(this->count == 0){
		this->parentLock->notifyAll();
	}

	this->lock.unlock();

	this->parentLock->unlock();
}

bool NodeCacheRef::isDeletable() noexcept {
	this->lock.lock();

	bool result = (this->count == 0);

	this->lock.unlock();

	return result;
}

} /* namespace alinous */


