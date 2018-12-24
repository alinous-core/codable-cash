/*
 * NodeCache.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btree/NodeCache.h"
#include "btree/AbstractTreeNode.h"
#include "btree/AbstractBtreeKey.h"
#include "btree/NodeCacheRef.h"

#include "base_thread/StackUnlocker.h"

namespace alinous {

CachedFpos::CachedFpos(const CachedFpos& inst) {
	this->fpos = inst.fpos;
}

CachedFpos::CachedFpos(uint64_t fpos) {
	this->fpos = fpos;
}

CachedFpos& CachedFpos::operator =(const CachedFpos& inst) {
	this->fpos = inst.fpos;
	return(*this);
}

int CachedFpos::hashCode() const noexcept {
	return (int)this->fpos;
}

int CachedFpos::ValueCompare::operator() (
		const CachedFpos* const _this, const CachedFpos* const object) const noexcept {
	return _this->fpos > object->fpos ? 1 : (_this->fpos < object->fpos ? -1 : 0);
}

NodeCache::NodeCache(int numDataBuffer, int numNodeBuffer) {
	this->numDataBuffer = numDataBuffer;
	this->numNodeBuffer = numNodeBuffer;

	this->nodes = new RawLinkedList<NodeCacheRef>();
	this->datas = new RawLinkedList<NodeCacheRef>();

	this->nodesMap = new HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>();
	this->datasMap = new HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>();

}

NodeCache::~NodeCache() {
	clear();

	delete this->nodes;
	delete this->datas;

	delete this->nodesMap;
	delete this->datasMap;
}

void NodeCache::clear() noexcept {
	{
		StackUnlocker __unlock(&this->nodesLock);
		clearList(this->nodes);
		clearMap(this->datasMap);
	}

	{
		StackUnlocker __unlock(&this->datasLock);
		clearList(this->datas);
		clearMap(this->nodesMap);
	}
}

void NodeCache::clearList(RawLinkedList<NodeCacheRef>* list) noexcept {
	auto it = list->iterator();
	while(it.hasNext()){
		NodeCacheRef* node = it.next();
		delete node;
	}
	list->clear();
}

void NodeCache::clearMap(HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map) noexcept {
	map->clear();
}

void NodeCache::add(AbstractTreeNode* node) {
	if(node->isLeaf()){
		internalAddNode(node, &this->datasLock, this->datasMap, this->datas);
	}
	else{
		internalAddNode(node, &this->nodesLock, this->nodesMap, this->nodes);
	}
}

void NodeCache::internalAddNode(AbstractTreeNode* node, SynchronizedLock* lock,
		HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map,
		RawLinkedList<NodeCacheRef>* list) {
	StackUnlocker __unlock(lock);

	NodeCacheRef* ref = new NodeCacheRef(node, lock);
	RawLinkedList<NodeCacheRef>::Element* element = list->add(0, ref);

	CachedFpos* fpos = new CachedFpos(node->getFpos());
	map->put(fpos, element);
}



} /* namespace alinous */


