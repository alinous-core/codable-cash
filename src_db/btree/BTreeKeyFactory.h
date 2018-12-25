/*
 * BTreeKeyFactory.h
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#ifndef BTREE_BTREEKEYFACTORY_H_
#define BTREE_BTREEKEYFACTORY_H_

#include <inttypes.h>

namespace alinous {

class AbstractBtreeKey;
class ByteBuffer;

class BTreeKeyFactory {
public:
	static const constexpr uint32_t INFINITY_KEY{0x01};
	static const constexpr uint32_t ULONG_KEY{0x02};

	BTreeKeyFactory();
	virtual ~BTreeKeyFactory();

	virtual AbstractBtreeKey* fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* BTREE_BTREEKEYFACTORY_H_ */
