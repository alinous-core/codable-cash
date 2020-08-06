/*
 * CdbOidValueList.cpp
 *
 *  Created on: 2020/06/01
 *      Author: iizuka
 */

#include "table_record_value/CdbOidValueList.h"

#include "engine/CdbOid.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

CdbOidValueList::CdbOidValueList(const CdbOidValueList& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_OID_LIST) {
	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		CdbOid* oid = inst.list.get(i);
		addOid(new CdbOid(*oid));
	}
}

CdbOidValueList::CdbOidValueList() : AbstractCdbValue(AbstractCdbValue::TYPE_OID_LIST) {

}

CdbOidValueList::~CdbOidValueList() {
	this->list.deleteElements();
}

int CdbOidValueList::binarySize() const {
	int total = sizeof(int8_t);

	int maxLoop = this->list.size();
	total += sizeof(int32_t);

	total += maxLoop * sizeof(uint64_t);

	return total;
}

void CdbOidValueList::toBinary(ByteBuffer* out) const {
	out->put(this->type);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		CdbOid* oid = this->list.get(i);
		uint64_t longOid = oid->getOid();

		out->putLong(longOid);
	}
}

void CdbOidValueList::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t longOid = in->getLong();

		addOid(new CdbOid(longOid));
	}
}

void CdbOidValueList::addOid(CdbOid* oid) noexcept {
	this->list.addElement(oid);
}

int CdbOidValueList::size() const noexcept {
	return this->list.size();
}

CdbOid* CdbOidValueList::get(int i) const noexcept {
	return this->list.get(i);
}

AbstractCdbValue* CdbOidValueList::copy() const noexcept {
	return new CdbOidValueList(*this);
}

AbstractCdbKey* CdbOidValueList::toKey() const noexcept {
	return nullptr;
}

} /* namespace codablecash */
