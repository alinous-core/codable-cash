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

class NodeCache {
public:
	NodeCache(int numDataBuffer, int numNodeBuffer);
	virtual ~NodeCache();

private:
	int numDataBuffer;
	int numNodeBuffer;

	RawLinkedList<AbstractTreeNode> nodes;
	HashMap<AbstractBtreeKey, AbstractTreeNode> nodesMap;

	RawLinkedList<AbstractTreeNode> datas;
	HashMap<AbstractBtreeKey, AbstractTreeNode> datasMap;


};

} /* namespace alinous */

#endif /* BTREE_NODECACHE_H_ */
