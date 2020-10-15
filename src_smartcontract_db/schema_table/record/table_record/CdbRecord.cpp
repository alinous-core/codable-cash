/*
 * CdbRecord.cpp
 *
 *  Created on: 2020/05/19
 *      Author: iizuka
 */

#include "schema_table/record/table_record/CdbRecord.h"
#include "schema_table/record/table_record/CdbDataFactory.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"

#include "schema_table/record/table_record_key/CdbRecordKey.h"

#include "base_io/ByteBuffer.h"

#include "filestore_block/IBlockObject.h"

#include "engine/CdbOid.h"

namespace codablecash {


CdbRecord::CdbRecord(const CdbRecord& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_RECORD) {
	this->oid = inst.oid != nullptr ? inst.oid->copy() : nullptr;

	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractCdbValue* v = inst.list.get(i);

		addValue(v != nullptr ? v->copy() : nullptr);
	}
}

CdbRecord::CdbRecord() : AbstractCdbValue(AbstractCdbValue::TYPE_RECORD) {
	this->oid = nullptr;
}

CdbRecord::~CdbRecord() {
	this->list.deleteElements();
	delete this->oid;
}

void CdbRecord::initNullColumns(int num) noexcept {
	for(int i = 0; i != num; ++i){
		addValue(nullptr);
	}
}

void CdbRecord::addValue(AbstractCdbValue* value) noexcept {
	this->list.addElement(value);
}

void CdbRecord::setValue(AbstractCdbValue* value, int i) noexcept {
	delete this->list.get(i);
	this->list.setElement(value, i);
}

void CdbRecord::removeColumnValue(int pos) noexcept {
	AbstractCdbValue* value = this->list.get(pos);

	this->list.remove(pos);
	delete value;
}

int CdbRecord::binarySize() const {
	int total = sizeof(int8_t);

	total += sizeof(uint8_t);
	bool notnull = this->oid != nullptr;
	if(notnull){
		total += this->oid->binarySize();
	}

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

	bool notnull = this->oid != nullptr;
	out->put(notnull ? 1 : 0);

	if(notnull){
		this->oid->toBinary(out);
	}

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

void CdbRecord::setOid(const CdbOid* oid) noexcept {
	delete this->oid;
	this->oid = oid->copy();
}

CdbRecord* CdbRecord::createFromBinary(ByteBuffer* in) {
	CdbDataFactory factory;
	CdbRecord* record = new CdbRecord();

	in->get(); // type

	uint8_t bl = in->get();

	if(bl != 0){
		record->oid = CdbOid::fromBinary(in);
	}

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		IBlockObject* blockObj = factory.makeDataFromBinary(in);
		AbstractCdbValue* value = dynamic_cast<AbstractCdbValue*>(blockObj);

		record->addValue(value);
	}

	return record;
}

void CdbRecord::fromBinary(ByteBuffer* in) {

	uint8_t bl = in->get();
	if(bl != 0){
		this->oid = CdbOid::fromBinary(in);
	}

	CdbDataFactory factory;
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
