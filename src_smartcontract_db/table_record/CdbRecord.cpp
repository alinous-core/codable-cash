/*
 * CdbRecord.cpp
 *
 *  Created on: 2020/05/19
 *      Author: iizuka
 */

#include "table_record/CdbRecord.h"
#include "table_record/CdbDataFactory.h"

#include "table_record_value/AbstractCdbValue.h"

#include "table_record_key/CdbRecordKey.h"

#include "base_io/ByteBuffer.h"

#include "filestore_block/IBlockObject.h"


namespace codablecash {


CdbRecord::CdbRecord(const CdbRecord& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_RECORD) {
	this->oid = inst.oid;

	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractCdbValue* v = inst.list.get(i);

		addValue(v != nullptr ? v->copy() : nullptr);
	}
}

CdbRecord::CdbRecord() : AbstractCdbValue(AbstractCdbValue::TYPE_RECORD) {
	this->oid = 0;
}

CdbRecord::~CdbRecord() {
	this->list.deleteElements();
}

void CdbRecord::initNullColumns(int num) noexcept {
	for(int i = 0; i != num; ++i){
		addValue(nullptr);
	}
}

void CdbRecord::addValue(AbstractCdbValue* value) noexcept {
	this->list.addElement(value);
}

int CdbRecord::binarySize() const {
	int total = sizeof(int8_t);

	total += sizeof(this->oid);

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
	out->put(this->type);

	out->putLong(this->oid);

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

void CdbRecord::setOid(uint64_t oid) noexcept {
	this->oid = oid;
}

CdbRecord* CdbRecord::createFromBinary(ByteBuffer* in) {
	CdbDataFactory factory;
	CdbRecord* record = new CdbRecord();

	in->get(); // type

	uint64_t oid = in->getLong();
	record->setOid(oid);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		IBlockObject* blockObj = factory.makeDataFromBinary(in);
		AbstractCdbValue* value = dynamic_cast<AbstractCdbValue*>(blockObj);

		record->addValue(value);
	}

	return record;
}

void CdbRecord::fromBinary(ByteBuffer* in) {
	CdbDataFactory factory;

	uint64_t oid = in->getLong();
	setOid(oid);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		IBlockObject* blockObj = factory.makeDataFromBinary(in);
		AbstractCdbValue* value = dynamic_cast<AbstractCdbValue*>(blockObj);

		addValue(value);
	}
}

const ArrayList<AbstractCdbValue>* CdbRecord::getValues() const noexcept {
	return &this->list;
}

AbstractCdbKey* CdbRecord::toKey() const noexcept {
	CdbRecordKey* key = new CdbRecordKey();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractCdbValue* value = this->list.get(i);

		AbstractCdbKey* k = (value == nullptr) ? nullptr : value->toKey();
		key->addKey(k);
	}

	return key;
}

AbstractCdbValue* CdbRecord::copy() const noexcept {
	return new CdbRecord(*this);
}

const AbstractCdbValue* CdbRecord::get(int pos) const noexcept {
	return this->list.get(pos);
}

} /* namespace codablecash */
