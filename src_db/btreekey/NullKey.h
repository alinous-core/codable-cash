/*
 * NullKey.h
 *
 *  Created on: 2020/08/15
 *      Author: iizuka
 */

#ifndef BTREEKEY_NULLKEY_H_
#define BTREEKEY_NULLKEY_H_

#include "btree/AbstractBtreeKey.h"

namespace alinous {

class NullKey : public AbstractBtreeKey {
public:
	NullKey();
	virtual ~NullKey();

	virtual bool isInfinity() const;
	virtual bool isNull() const;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static NullKey* fromBinary(ByteBuffer* in);

	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;
	virtual AbstractBtreeKey* clone() const noexcept;
};

} /* namespace alinous */

#endif /* BTREEKEY_NULLKEY_H_ */
