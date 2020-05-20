/*
 * CdbDataFactory.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record/CdbDataFactory.h"

#include "base_io/ByteBuffer.h"

#include "filestore_block/IBlockObject.h"

namespace codablecash {

CdbDataFactory::CdbDataFactory() {

}

CdbDataFactory::~CdbDataFactory() {

}

IBlockObject* CdbDataFactory::makeDataFromBinary(ByteBuffer* in) {

}

} /* namespace codablecash */
