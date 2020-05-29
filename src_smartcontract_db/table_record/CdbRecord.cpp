/*
 * CdbRecord.cpp
 *
 *  Created on: 2020/05/19
 *      Author: iizuka
 */

#include "table_record/CdbRecord.h"
#include "table_record/CdbDataFactory.h"

#include "table_record_value/AbstractCdbValue.h"

#include "base_io/ByteBuffer.h"

#include "filestore_block/IBlockObject.h"

namespace codablecash {

CdbRecord::CdbRecord() {

}

CdbRecord::~CdbRecord() {
	this->list.deleteElements();
}

void CdbRecord::addValue(AbstractCdbValue* value) noexcept {
	this->list.addElement(value);
}

int CdbRecord::binarySize() const {
	int total = 0;

	int maxLoop = this->list.size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		AbstractCdbValue* value = this->list.get(i);

		if(value == nullptr){
			total += sizeof(uint8_t);
		}
		else{
			total += value->binarySize();
		}
	}

	return total;
}

void CdbRecord::toBinary(ByteBuffer* out) const {
	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractCdbValue* value = this->list.get(i);

		if(value == nullptr){
			out->put((char)0);
		}
		else{
			value->toBinary(out);
		}
	}
}

CdbRecord* CdbRecord::fromBinary(ByteBuffer* in) {
	CdbDataFactory factory;
	CdbRecord* record = new CdbRecord();

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		IBlockObject* blockObj = factory.makeDataFromBinary(in);
		AbstractCdbValue* value = dynamic_cast<AbstractCdbValue*>(blockObj);

		record->addValue(value);
	}

	return record;
}

} /* namespace codablecash */
