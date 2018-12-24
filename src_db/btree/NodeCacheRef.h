/*
 * NodeCacheRef.h
 *
 *  Created on: 2018/12/24
 *      Author: iizuka
 */

#ifndef BTREE_NODECACHEREF_H_
#define BTREE_NODECACHEREF_H_

#include "base_thread/SynchronizedLock.h"

namespace alinous {

class AbstractTreeNode;

class NodeCacheRef {
public:
	NodeCacheRef(const NodeCacheRef& inst) = delete;
	explicit NodeCacheRef(AbstractTreeNode* node, SynchronizedLock* parentLock);
	virtual ~NodeCacheRef();

	void inc();
	void dec();
	bool isDeletable() noexcept;

	AbstractTreeNode* getNode() const noexcept {
		return this->node;
	}
private:
	int count;
	SynchronizedLock lock;
	SynchronizedLock* parentLock;

	AbstractTreeNode* node;
};

} /* namespace alinous */

#endif /* BTREE_NODECACHEREF_H_ */
