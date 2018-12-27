/*
 * LongKey.h
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#ifndef BTREEKEY_ULONGKEY_H_
#define BTREEKEY_ULONGKEY_H_

#include "btree/AbstractBtreeKey.h"

#include <inttypes.h>

namespace alinous {

class ULongKey: public AbstractBtreeKey {
public:
	explicit ULongKey(uint64_t value);
	virtual ~ULongKey();

	uint64_t getValue() const noexcept {
		return value;
	}

	void setValue(uint64_t value) noexcept {
		this->value = value;
	}

	virtual bool isInfinity() { return false; }

	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);
	static ULongKey* fromBinary(ByteBuffer* in);

	virtual int compareTo(AbstractBtreeKey* key) const noexcept;
	virtual AbstractBtreeKey* clone() const noexcept;

private:
	uint64_t value;
};

} /* namespace alinous */

#endif /* BTREEKEY_ULONGKEY_H_ */
