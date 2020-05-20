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

class AbstractCdbValue : public IBlockObject {
public:
	static const constexpr uint8_t TYPE_BYTE{1};
	static const constexpr uint8_t TYPE_SHORT{2};
	static const constexpr uint8_t TYPE_INT{3};
	static const constexpr uint8_t TYPE_LONG{4};
	static const constexpr uint8_t TYPE_STRING{5};

	explicit AbstractCdbValue(uint8_t type);
	virtual ~AbstractCdbValue();

protected:
	uint8_t type;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_ABSTRACTCDBVALUE_H_ */
