/*
 * CdbShortValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbShortValue.h"

namespace codablecash {

CdbShortValue::CdbShortValue() : AbstractCdbValue(AbstractCdbValue::TYPE_SHORT) {

}

CdbShortValue::~CdbShortValue() {

}

int CdbShortValue::compareTo(const AbstractBtreeKey* key) const noexcept {
}

AbstractBtreeKey* CdbShortValue::clone() const noexcept {
}

int CdbShortValue::binarySize() const {
}

void CdbShortValue::toBinary(ByteBuffer* out) const {
}

void CdbShortValue::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
