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
	clearList(this->nodes);
	clearList(this->datas);

	clearMap(this->nodesMap);
	clearMap(this->datasMap);
}

void NodeCache::clearList(RawLinkedList<NodeCacheRef>* list) noexcept {
	this->lock.lock();
	StackUnlocker __unlock(&this->lock);

	auto it = list->iterator();
	while(it.hasNext()){
		NodeCacheRef* node = it.next();
		delete node;
	}
	list->clear();
}

void NodeCache::add(AbstractTreeNode* node) {
	this->lock.lock();
	StackUnlocker __unlock(&this->lock);

}

void NodeCache::clearMap(HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map) noexcept {
	map->clear();
}

} /* namespace alinous */
