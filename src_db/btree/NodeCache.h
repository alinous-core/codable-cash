/*
 * NodeCache.h
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#ifndef BTREE_NODECACHE_H_
#define BTREE_NODECACHE_H_

#include "base/RawLinkedList.h"
#include "base/HashMap.h"

namespace alinous {

class AbstractTreeNode;
class AbstractBtreeKey;

class NodeCache {
public:
	NodeCache(const NodeCache& inst) = delete;
	NodeCache(int numDataBuffer, int numNodeBuffer);
	virtual ~NodeCache();

	void clear() noexcept;

private:
	void clearList(RawLinkedList<AbstractTreeNode>* list) noexcept;
	void clearMap(HashMap<AbstractBtreeKey, RawLinkedList<AbstractTreeNode>::Element>* map) noexcept;
private:
	int numDataBuffer;
	int numNodeBuffer;

	RawLinkedList<AbstractTreeNode>* nodes;
	HashMap<AbstractBtreeKey, RawLinkedList<AbstractTreeNode>::Element>* nodesMap;

	RawLinkedList<AbstractTreeNode>* datas;
	HashMap<AbstractBtreeKey, RawLinkedList<AbstractTreeNode>::Element>* datasMap;


};

} /* namespace alinous */

#endif /* BTREE_NODECACHE_H_ */
