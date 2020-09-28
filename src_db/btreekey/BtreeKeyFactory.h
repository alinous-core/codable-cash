/*
 * BTreeKeyFactory.h
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#ifndef BTREE_BTREEKEYFACTORY_H_
#define BTREE_BTREEKEYFACTORY_H_

#include <cstdint>

namespace alinous {

class AbstractBtreeKey;
class ByteBuffer;

class BtreeKeyFactory {
public:
	static const constexpr uint32_t NULL_KEY{0x01};
	static const constexpr uint32_t INFINITY_KEY{0x02};
	static const constexpr uint32_t ULONG_KEY{0x03};

	BtreeKeyFactory();
	virtual ~BtreeKeyFactory();

	virtual AbstractBtreeKey* fromBinary(uint32_t keyType, ByteBuffer* in) const;
	virtual BtreeKeyFactory* copy() const noexcept;
};

} /* namespace alinous */

#endif /* BTREE_BTREEKEYFACTORY_H_ */
