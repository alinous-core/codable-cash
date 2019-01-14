/*
 * AbstractBtreeDataFactory.h
 *
 *  Created on: 2018/12/27
 *      Author: iizuka
 */

#ifndef BTREE_ABSTRACTBTREEDATAFACTORY_H_
#define BTREE_ABSTRACTBTREEDATAFACTORY_H_

namespace alinous {

class IBlockObject;
class ByteBuffer;
class BtreeStorage;
class DataNode;
class AbstractBtreeKey;

class AbstractBtreeDataFactory {
public:
	virtual ~AbstractBtreeDataFactory();
	virtual IBlockObject* makeDataFromBinary(ByteBuffer* in) = 0;
	virtual void registerData(const IBlockObject* data, DataNode* dataNode, BtreeStorage* store) const;
	virtual bool beforeRemove(DataNode* dataNode, BtreeStorage* store, const AbstractBtreeKey* key) const;
};

} /* namespace alinous */

#endif /* BTREE_ABSTRACTBTREEDATAFACTORY_H_ */
