/*
 * CdbIntValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbIntValue.h"

namespace codablecash {

CdbIntValue::CdbIntValue() : AbstractCdbValue(AbstractCdbValue::TYPE_INT) {

}

CdbIntValue::~CdbIntValue() {

}

int CdbIntValue::compareTo(const AbstractBtreeKey* key) const noexcept {
}

AbstractBtreeKey* CdbIntValue::clone() const noexcept {
}

int CdbIntValue::binarySize() const {
}

void CdbIntValue::toBinary(ByteBuffer* out) const {
}

void CdbIntValue::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
