/*
 * CdbKeyFactory.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record/CdbKeyFactory.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

CdbKeyFactory::CdbKeyFactory() {

}

CdbKeyFactory::~CdbKeyFactory() {

}

AbstractBtreeKey* CdbKeyFactory::fromBinary(uint32_t keyType, ByteBuffer* in) const {

	return BtreeKeyFactory::fromBinary(keyType, in);
}

} /* namespace codablecash */
