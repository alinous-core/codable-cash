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

class AbstractBtreeDataFactory {
public:
	virtual ~AbstractBtreeDataFactory();
	virtual IBlockObject* makeDataFromBinary(ByteBuffer* in) = 0;
};

} /* namespace alinous */

#endif /* BTREE_ABSTRACTBTREEDATAFACTORY_H_ */
