/*
 * NodeCache.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btree/NodeCache.h"
#include "btree/AbstractTreeNode.h"
#include "btree/AbstractBtreeKey.h"

namespace alinous {

NodeCache::NodeCache(int numDataBuffer, int numNodeBuffer) {
	this->numDataBuffer = numDataBuffer;
	this->numNodeBuffer = numNodeBuffer;

	this->nodes = new RawLinkedList<AbstractTreeNode>();
	this->datas = new RawLinkedList<AbstractTreeNode>();

	this->nodesMap = new HashMap<AbstractBtreeKey, RawLinkedList<AbstractTreeNode>::Element>();
	this->datasMap = new HashMap<AbstractBtreeKey, RawLinkedList<AbstractTreeNode>::Element>();

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

void NodeCache::clearList(RawLinkedList<AbstractTreeNode>* list) noexcept {
	auto it = list->iterator();
	while(it.hasNext()){
		AbstractTreeNode* node = it.next();
		delete node;
	}
	list->clear();
}

void NodeCache::clearMap(HashMap<AbstractBtreeKey, RawLinkedList<AbstractTreeNode>::Element>* map) noexcept {
	map->clear();
}

} /* namespace alinous */
