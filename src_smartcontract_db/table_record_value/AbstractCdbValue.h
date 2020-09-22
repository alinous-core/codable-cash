/*
 * AbstractCdbValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_ABSTRACTCDBVALUE_H_
#define TABLE_RECORD_VALUE_ABSTRACTCDBVALUE_H_

#include <cstdint>

#include "filestore_block/IBlockObject.h"

using namespace alinous;

namespace codablecash {

class AbstractCdbKey;

class AbstractCdbValue : public IBlockObject {
public:
	static const constexpr uint8_t TYPE_BYTE{1};
	static const constexpr uint8_t TYPE_SHORT{2};
	static const constexpr uint8_t TYPE_INT{3};
	static const constexpr uint8_t TYPE_LONG{4};
	static const constexpr uint8_t TYPE_STRING{5};

	static const constexpr uint8_t TYPE_RECORD{6};
	static const constexpr uint8_t TYPE_OID_LIST{7};

	explicit AbstractCdbValue(uint8_t type);
	virtual ~AbstractCdbValue();

	virtual void fromBinary(ByteBuffer* in) = 0;

	virtual AbstractCdbValue* copy() const noexcept = 0;
	virtual AbstractCdbKey* toKey() const noexcept = 0;

	static bool isCompatible(uint8_t type, uint8_t type2) noexcept;

	uint8_t getType() const noexcept {
		return type;
	}

protected:
	uint8_t type;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_ABSTRACTCDBVALUE_H_ */
