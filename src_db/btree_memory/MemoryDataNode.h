/*
 * MemoryDataNode.h
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYDATANODE_H_
#define BTREE_MEMORY_MEMORYDATANODE_H_

#include "btree_memory/AbstractMemoryTreeNode.h"

namespace alinous {

class AbstractBtreeKey;
class IBlockObject;

class MemoryDataNode : public AbstractMemoryTreeNode {
public:
	explicit MemoryDataNode(AbstractBtreeKey* key);
	virtual ~MemoryDataNode();

	virtual bool isData() const noexcept { return true; }

	void setData(IBlockObject* data) noexcept;

	IBlockObject* getData() const noexcept {
		return data;
	}

private:
	IBlockObject* data;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYDATANODE_H_ */
