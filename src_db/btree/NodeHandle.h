/*
 * NodeHandle.h
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#ifndef BTREE_NODEHANDLE_H_
#define BTREE_NODEHANDLE_H_

#include "base/RawArrayPrimitive.h"

#include <inttypes.h>

namespace alinous {

class NodeCacheRef;
class TreeNode;
class DataNode;
class AbstractBtreeKey;

class NodeHandle {
public:
	NodeHandle(const NodeHandle& inst) = delete;
	explicit NodeHandle(NodeCacheRef* ref);
	virtual ~NodeHandle();

	bool isRoot() const;
	bool isLeaf() const;
	bool isData() const noexcept;

	NodeCacheRef* getRef() const noexcept;
	AbstractBtreeKey* getKey() const noexcept;

	TreeNode* toTreeNode() const;
	DataNode* toDataNode() const;

	RawArrayPrimitive<uint64_t>* getInnerNodeFpos() const;
private:
	NodeCacheRef* ref;
};

} /* namespace alinous */

#endif /* BTREE_NODEHANDLE_H_ */
