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
	static const constexpr uint32_t TYPE_BYTE{11};
	static const constexpr uint32_t TYPE_SHORT{12};
	static const constexpr uint32_t TYPE_INT{13};
	static const constexpr uint32_t TYPE_LONG{14};
	static const constexpr uint32_t TYPE_STRING{15};

	static const constexpr uint32_t TYPE_RECORD_KEY{16};
	static const constexpr uint32_t TYPE_OID_KEY{17};

	explicit AbstractCdbKey(uint32_t type);
	virtual ~AbstractCdbKey();

	virtual bool isInfinity() const;
	virtual bool isNull() const;
	virtual void fromBinary(ByteBuffer* in) = 0;

protected:
	uint32_t type;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_ABSTRACTCDBKEY_H_ */
