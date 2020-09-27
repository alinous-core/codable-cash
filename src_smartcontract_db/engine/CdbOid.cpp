/*
 * CdbOid.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "engine/CdbOid.h"
#include "engine/CdbException.h"

#include "base_io/ByteBuffer.h"

#include "table_record_local/LocalCdbOid.h"

#include "table_record_key/AbstractCdbKey.h"
#include "table_record_key/CdbOidKey.h"

namespace codablecash {

CdbOid::CdbOid(const CdbOid& inst) {
	this->oid = inst.oid;
}

CdbOid::CdbOid(uint64_t oid) {
	this->oid = oid;
}

CdbOid::~CdbOid() {

}

uint8_t CdbOid::getTypeCode() const noexcept {
	return CdbOid::CDB_OID;
}

bool CdbOid::isLocal() const noexcept {
	return false;
}

bool CdbOid::equals(const CdbOid* other) const noexcept {
	return isLocal() == other->isLocal() && this->oid == other->oid;
}

int CdbOid::binarySize() const {
	int total = sizeof(uint8_t);
	total += sizeof(uint64_t); // oid

	return total;
}

void CdbOid::toBinary(ByteBuffer* out) const {
	uint8_t type = getTypeCode();
	out->put(type);
	out->putLong(this->oid);
}

CdbOid* CdbOid::fromBinary(ByteBuffer* in) {
	uint8_t type = in->get();
	uint64_t v = in->getLong();

	CdbOid* ptr = nullptr;

	switch(type){
	case CdbOid::CDB_OID:
		ptr = new CdbOid(v);
		break;
	case CdbOid::CDB_LOCAL_OID:
		ptr = new LocalCdbOid(v);
		break;
	default:
		 throw new CdbException(L"wrong oid type.", __FILE__, __LINE__);
	}

	return ptr;
}

CdbOid* CdbOid::copy() const noexcept {
	return new CdbOid(*this);
}

AbstractCdbKey* CdbOid::toKey() const noexcept {
	return new CdbOidKey(this);
}

IBlockObject* CdbOid::copyData() const noexcept {
	return copy();
}

int CdbOid::hashCode() const {
	return (int)this->oid;
}

int CdbOid::ValueCompare::operator ()(const CdbOid* const _this, const CdbOid* const object) const noexcept {
	uint8_t this_type = _this->getTypeCode();
	uint8_t object_type = object->getTypeCode();

	uint8_t diff = this_type - object_type;
	if(diff != 0){
		return diff;
	}

	return ((int)_this->oid) - ((int)object->oid);
}

} /* namespace codablecash */
