/*
 * TempValue.cpp
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#include "db/db_btree/TempValue.h"
#include "base_io/ReverseByteBuffer.h"

namespace alinous {

TempValue::TempValue(uint64_t value) {
	this->value = value;
}

TempValue::~TempValue() {
}

int TempValue::binarySize() const {
	return sizeof(TmpValueFactory::TMPVALUE) + sizeof(this->value);
}

void TempValue::toBinary(ByteBuffer* out) const {
	out->putInt(TmpValueFactory::TMPVALUE);
	out->putLong(this->value);
}

IBlockObject* TempValue::copyData() const noexcept {
	return new TempValue(this->value);
}


/**************************************************/

alinous::TmpValueFactory::~TmpValueFactory() {

}

IBlockObject* TmpValueFactory::makeDataFromBinary(ByteBuffer* in) {
	int type = in->getInt();

	uint64_t value = in->getLong();
	return new TempValue(value);

}
} /* namespace alinous */


