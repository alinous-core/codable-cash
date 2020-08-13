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
	CachedFpos(const CachedFpos& inst);
	explicit CachedFpos(uint64_t fpos);

	CachedFpos &operator=(const CachedFpos &inst);

	int hashCode() const noexcept;
	class ValueCompare {
	public:
		int operator() (const CachedFpos* const _this, const  CachedFpos* const object) const noexcept;
	};

	uint64_t fpos;
};

class NodeCache {
public:
	NodeCache(const NodeCache& inst) = delete;
	NodeCache(int numDataBuffer, int numNodeBuffer);
	virtual ~NodeCache();

	void clear() noexcept;

	void add(AbstractTreeNode* node) noexcept;
	NodeCacheRef* get(uint64_t fpos) noexcept;
	void remove(NodeCacheRef* ref) noexcept;

private:
	void internalAddNode(AbstractTreeNode* node, SynchronizedLock* lock,
			HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map,
			RawLinkedList<NodeCacheRef>* list, int max) noexcept;
	void cacheOut(HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map, RawLinkedList<NodeCacheRef>* list,
			SynchronizedLock* lock) noexcept;

	void onCacheHit(RawLinkedList<NodeCacheRef>::Element* element, RawLinkedList<NodeCacheRef>* list, SynchronizedLock* lock) noexcept;
	void removeCachedRef(NodeCacheRef* ref, SynchronizedLock* lock) noexcept;

	void internalRemove(AbstractTreeNode* node, SynchronizedLock* lock, HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map,
			RawLinkedList<NodeCacheRef>* list) noexcept;

	void clearList(RawLinkedList<NodeCacheRef>* list) noexcept;
	void clearMap(HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* map) noexcept;
private:
	int numDataBuffer;
	int numNodeBuffer;

	RawLinkedList<NodeCacheRef>* nodes;
	HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* nodesMap;

	RawLinkedList<NodeCacheRef>* datas;
	HashMap<CachedFpos, RawLinkedList<NodeCacheRef>::Element>* datasMap;

	SynchronizedLock nodesLock;
	SynchronizedLock datasLock;
};

} /* namespace alinous */

#endif /* BTREE_NODECACHE_H_ */
