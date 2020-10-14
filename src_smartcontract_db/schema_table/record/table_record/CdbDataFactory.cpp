/*
 * CdbDataFactory.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "schema_table/record/table_record/CdbDataFactory.h"

#include "base_io/ByteBuffer.h"

#include "filestore_block/IBlockObject.h"

#include "engine/CdbException.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"
#include "schema_table/record/table_record_value/CdbByteValue.h"
#include "schema_table/record/table_record_value/CdbShortValue.h"
#include "schema_table/record/table_record_value/CdbIntValue.h"
#include "schema_table/record/table_record_value/CdbLongValue.h"
#include "schema_table/record/table_record_value/CdbStringValue.h"
#include "schema_table/record/table_record_value/CdbOidValueList.h"

#include "schema_table/record/table_record/CdbRecord.h"

namespace codablecash {

CdbDataFactory::CdbDataFactory() {

}

CdbDataFactory::~CdbDataFactory() {

}

IBlockObject* CdbDataFactory::makeDataFromBinary(ByteBuffer* in) {
	uint8_t type = in->get();
	AbstractCdbValue* value = nullptr;

	switch(type){
	case AbstractCdbValue::TYPE_BYTE:
		value = new CdbByteValue();
		break;
	case AbstractCdbValue::TYPE_SHORT:
		value = new CdbShortValue();
		break;
	case AbstractCdbValue::TYPE_INT:
		value = new CdbIntValue();
		break;
	case AbstractCdbValue::TYPE_LONG:
		value = new CdbLongValue();
		break;
	case AbstractCdbValue::TYPE_STRING:
		value = new CdbStringValue();
		break;
	case AbstractCdbValue::TYPE_RECORD:
		value = new CdbRecord();
		break;
	case AbstractCdbValue::TYPE_OID_LIST:
		value = new CdbOidValueList();
		break;
	case 0:
		return nullptr;
	default:
		throw new CdbException(__FILE__, __LINE__);
	}

	value->fromBinary(in);

	return value;
}

AbstractBtreeDataFactory* CdbDataFactory::copy() const noexcept {
	return new CdbDataFactory();
}

} /* namespace codablecash */
