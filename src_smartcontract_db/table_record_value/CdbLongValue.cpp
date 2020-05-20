/*
 * CdbLongValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbLongValue.h"

namespace codablecash {

CdbLongValue::CdbLongValue() : AbstractCdbValue(AbstractCdbValue::TYPE_LONG) {

}

CdbLongValue::~CdbLongValue() {

}

int CdbLongValue::compareTo(const AbstractBtreeKey* key) const noexcept {
}

AbstractBtreeKey* CdbLongValue::clone() const noexcept {
}

int CdbLongValue::binarySize() const {
}

void CdbLongValue::toBinary(ByteBuffer* out) const {
}

void CdbLongValue::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
