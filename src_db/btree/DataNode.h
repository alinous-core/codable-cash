/*
 * DataNode.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_DATANODE_H_
#define BTREE_DATANODE_H_

#include "btree/AbstractTreeNode.h"

#include "base/RawArrayPrimitive.h"

namespace alinous {

class BtreeKeyFactory;
class AbstractBtreeKey;

class DataNode: public AbstractTreeNode {
public:
	DataNode &operator=(const DataNode &o) = delete;
	explicit DataNode(const DataNode& inst);
	DataNode();
	explicit DataNode(AbstractBtreeKey* key);
	virtual ~DataNode();

	virtual bool isData() const noexcept { return true; }
	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static DataNode* fromBinary(ByteBuffer* in, BtreeKeyFactory* factory);

	uint64_t getDataFpos() const noexcept;
	void setDataFpos(uint64_t fpos) noexcept;

	virtual IBlockObject* copyData() const noexcept;

private:
	uint64_t datafpos;
};

} /* namespace alinous */

#endif /* BTREE_DATANODE_H_ */
