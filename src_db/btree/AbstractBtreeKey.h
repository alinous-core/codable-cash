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

	virtual bool isInfinity() const = 0;
	virtual bool isNull() const = 0;

	virtual int compareTo(const AbstractBtreeKey* key) const noexcept = 0;
	virtual AbstractBtreeKey* clone()  const noexcept = 0;

	virtual IBlockObject* copyData() const noexcept;
};

} /* namespace alinous */

#endif /* BTREE_ABSTRACTBTREEKEY_H_ */
