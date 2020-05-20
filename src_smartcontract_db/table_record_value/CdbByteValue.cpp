/*
 * CdbByteValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbByteValue.h"

namespace codablecash {

CdbByteValue::CdbByteValue() : AbstractCdbValue(AbstractCdbValue::TYPE_BYTE) {

}

CdbByteValue::~CdbByteValue() {

}

int CdbByteValue::compareTo(const AbstractBtreeKey* key) const noexcept {
}

AbstractBtreeKey* CdbByteValue::clone() const noexcept {
}

int CdbByteValue::binarySize() const {
}

void CdbByteValue::toBinary(ByteBuffer* out) const {
}

void CdbByteValue::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
