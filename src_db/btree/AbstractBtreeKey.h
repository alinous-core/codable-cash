/*
 * AbstractBtreeKey.h
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#ifndef BTREE_ABSTRACTBTREEKEY_H_
#define BTREE_ABSTRACTBTREEKEY_H_

#include "filestore_block/IBlockObject.h"

namespace alinous {

class AbstractBtreeKey: public IBlockObject {
public:
	AbstractBtreeKey();
	virtual ~AbstractBtreeKey();

	virtual bool isInfinity() = 0;
};

} /* namespace alinous */

#endif /* BTREE_ABSTRACTBTREEKEY_H_ */
