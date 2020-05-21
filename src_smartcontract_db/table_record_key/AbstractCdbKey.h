/*
 * AbstractCdbKey.h
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_KEY_ABSTRACTCDBKEY_H_
#define TABLE_RECORD_KEY_ABSTRACTCDBKEY_H_

#include "btree/AbstractBtreeKey.h"
#include <cstdint>

namespace alinous {
}
using namespace alinous;

namespace codablecash {

class AbstractCdbKey : public AbstractBtreeKey {
public:
	static const constexpr uint32_t TYPE_BYTE{1};
	static const constexpr uint32_t TYPE_SHORT{2};
	static const constexpr uint32_t TYPE_INT{3};
	static const constexpr uint32_t TYPE_LONG{4};
	static const constexpr uint32_t TYPE_STRING{5};

	explicit AbstractCdbKey(uint32_t type);
	virtual ~AbstractCdbKey();

	virtual bool isInfinity() const;
	virtual void fromBinary(ByteBuffer* in) = 0;

protected:
	uint32_t type;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_ABSTRACTCDBKEY_H_ */
