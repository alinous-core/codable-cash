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

	virtual bool isInfinity() const;
	virtual bool isNull() const;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static InfinityKey* fromBinary(ByteBuffer* in);

	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;
	virtual AbstractBtreeKey* clone() const noexcept;
};

} /* namespace alinous */

#endif /* BTREE_INFINITYKEY_H_ */
