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
#include "base_thread/SynchronizedLock.h"

namespace alinous {

class AbstractTreeNode;
class NodeCacheRef;
class AbstractBtreeKey;


class CachedFpos {
public:
	uint64_t fpos;
};

class NodeCache {
public:
	NodeCache(const NodeCache& inst) = delete;
	NodeCache(int numDataBuffer, int numNodeBuffer);
	virtual ~NodeCache();

	void clear() noexcept;

	void add(AbstractTreeNode* node);


private:
	void clearList(RawLinkedList<NodeCacheRef>* list) noexcept;
	void clearMap(HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map) noexcept;
private:
	int numDataBuffer;
	int numNodeBuffer;

	RawLinkedList<NodeCacheRef>* nodes;
	HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* nodesMap;

	RawLinkedList<NodeCacheRef>* datas;
	HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* datasMap;

	SynchronizedLock lock;
};

} /* namespace alinous */

#endif /* BTREE_NODECACHE_H_ */
