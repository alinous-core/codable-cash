/*
 * InfinityKey.h
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#ifndef BTREE_INFINITYKEY_H_
#define BTREE_INFINITYKEY_H_

#include "btree/AbstractBtreeKey.h"

namespace alinous {

class InfinityKey: public AbstractBtreeKey {
public:
	InfinityKey();
	virtual ~InfinityKey();

	virtual bool isInfinity();
};

} /* namespace alinous */

#endif /* BTREE_INFINITYKEY_H_ */
