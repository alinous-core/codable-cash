/*
 * NodeCache.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btree_cache/NodeCache.h"
#include "btree_cache/NodeCacheRef.h"

#include "btree/AbstractTreeNode.h"
#include "btree/AbstractBtreeKey.h"


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
		clearMap(this->nodesMap);
	}

	{
		StackUnlocker __unlock(&this->datasLock);
		clearList(this->datas);
		clearMap(this->datasMap);
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

NodeCacheRef* NodeCache::get(uint64_t fpos) noexcept {
	CachedFpos key(fpos);

	{
		StackUnlocker __unlock(&this->nodesLock);
		RawLinkedList<NodeCacheRef>::Element* element = this->nodesMap->get(key);
		if(element != nullptr){
			onCacheHit(element, this->nodes, &this->nodesLock);
			return element->data;
		}
	}

	{
		StackUnlocker __unlock(&this->datasLock);
		RawLinkedList<NodeCacheRef>::Element* element = this->datasMap->get(key);
		if(element != nullptr){
			onCacheHit(element, this->datas, &this->datasLock);
			return element->data;
		}
	}

	return nullptr;
}

void NodeCache::onCacheHit(RawLinkedList<NodeCacheRef>::Element* element,
							RawLinkedList<NodeCacheRef>* list, SynchronizedLock* lock) noexcept {
	list->moveElementToTop(element);
}

void NodeCache::add(AbstractTreeNode* node) noexcept {
	if(node->isData()){
		internalAddNode(node, &this->datasLock, this->datasMap, this->datas, this->numDataBuffer);
	}
	else{
		internalAddNode(node, &this->nodesLock, this->nodesMap, this->nodes, this->numNodeBuffer);
	}
}

void NodeCache::internalAddNode(AbstractTreeNode* node, SynchronizedLock* lock,
		HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map,
		RawLinkedList<NodeCacheRef>* list, int max) noexcept {
	StackUnlocker __unlock(lock);

	NodeCacheRef* ref = new NodeCacheRef(node, lock);
	RawLinkedList<NodeCacheRef>::Element* element = list->add(0, ref);

	CachedFpos fpos(node->getFpos());
	map->put(&fpos, element);

	if(list->size() > max){
		cacheOut(map, list, lock);
	}
}

void NodeCache::remove(NodeCacheRef* ref) noexcept {
	if(ref->getNode()->isData()){
		internalRemove(ref->getNode(), &this->datasLock, this->datasMap, this->datas);
	}
	else{
		internalRemove(ref->getNode(), &this->nodesLock, this->nodesMap, this->nodes);
	}
}

void NodeCache::internalRemove(AbstractTreeNode* node, SynchronizedLock* lock, HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map,
		RawLinkedList<NodeCacheRef>* list) noexcept {
	StackUnlocker __unlock(lock);

	uint64_t fpos = node->getFpos();
	CachedFpos cfpos(fpos);

	RawLinkedList<NodeCacheRef>::Element* element = map->get(&cfpos);
	NodeCacheRef* ref = element->data;
	map->remove(&cfpos);

	list->remove(element);
	removeCachedRef(ref, lock);
}

void NodeCache::cacheOut(HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map,
		RawLinkedList<NodeCacheRef>* list, SynchronizedLock* lock) noexcept {
	int lastIndex = list->size() - 1;

	NodeCacheRef* ref = list->get(lastIndex);
	list->remove(lastIndex);

	uint64_t fpos = ref->getNode()->getFpos();
	CachedFpos key(fpos);

	map->remove(&key);

	removeCachedRef(ref, lock);
}

void NodeCache::removeCachedRef(NodeCacheRef* ref, SynchronizedLock* lock) noexcept {
	while(!ref->isDeletable()){
		lock->wait();
	}

	delete ref;
}

} /* namespace alinous */
