/*
 * CdbKeyFactory.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record/CdbKeyFactory.h"

#include "table_record_key/AbstractCdbKey.h"

#include "base_io/ByteBuffer.h"

#include "table_record_key/CdbByteKey.h"
#include "table_record_key/CdbShortKey.h"
#include "table_record_key/CdbIntKey.h"
#include "table_record_key/CdbLongKey.h"
#include "table_record_key/CdbStringKey.h"

namespace codablecash {

CdbKeyFactory::CdbKeyFactory() {

}

CdbKeyFactory::~CdbKeyFactory() {

}

AbstractBtreeKey* CdbKeyFactory::fromBinary(uint32_t keyType, ByteBuffer* in) const {
	AbstractCdbKey* retKey = nullptr;

	switch(keyType){
	case AbstractCdbKey::TYPE_BYTE:
		retKey = new CdbByteKey();
		break;
	case AbstractCdbKey::TYPE_SHORT:
		retKey = new CdbShortKey();
		break;
	case AbstractCdbKey::TYPE_INT:
		retKey = new CdbIntKey();
		break;
	case AbstractCdbKey::TYPE_LONG:
		retKey = new CdbLongKey();
		break;
	case AbstractCdbKey::TYPE_STRING:
		retKey = new CdbStringKey();
		break;
	default:
		break;
	}

	if(retKey != nullptr){
		retKey->fromBinary(in);
		return retKey;
	}

	return BtreeKeyFactory::fromBinary(keyType, in);;
}

} /* namespace codablecash */
