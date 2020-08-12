/*
 * AbstractMemoryTreeNode.h
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_ABSTRACTMEMORYTREENODE_H_
#define BTREE_MEMORY_ABSTRACTMEMORYTREENODE_H_

namespace alinous {

class AbstractBtreeKey;

class AbstractMemoryTreeNode {
public:
	explicit AbstractMemoryTreeNode(AbstractBtreeKey* key);
	virtual ~AbstractMemoryTreeNode();

	virtual bool isData() const noexcept = 0;

	AbstractBtreeKey* getKey() const noexcept {
		return this->key;
	}
protected:
	AbstractBtreeKey* key;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_ABSTRACTMEMORYTREENODE_H_ */
