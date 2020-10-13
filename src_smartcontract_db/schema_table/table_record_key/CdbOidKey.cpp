/*
 * CdbOidKey.cpp
 *
 *  Created on: 2020/09/26
 *      Author: iizuka
 */

#include "schema_table/table_record_key/CdbOidKey.h"

#include "engine/CdbOid.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

CdbOidKey::CdbOidKey() : AbstractCdbKey(AbstractCdbKey::TYPE_OID_KEY) {
	this->oid = nullptr;
}

CdbOidKey::CdbOidKey(const CdbOidKey& inst) : AbstractCdbKey(AbstractCdbKey::TYPE_OID_KEY) {
	this->oid = inst.oid->copy();
}

CdbOidKey::CdbOidKey(const CdbOid* oid) : AbstractCdbKey(AbstractCdbKey::TYPE_OID_KEY) {
	this->oid = oid->copy();
}

CdbOidKey::~CdbOidKey() {
	delete this->oid;
}

AbstractBtreeKey* CdbOidKey::clone() const noexcept {
	return new CdbOidKey(*this);
}

int CdbOidKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}
	else if(key->isNull()){
		return 1;
	}

	static CdbOid::ValueCompare comp;
	const CdbOidKey* other = dynamic_cast<const CdbOidKey*>(key);

	return comp(this->oid, other->oid);
}

int CdbOidKey::binarySize() const {
	return sizeof(uint32_t) + this->oid->binarySize();
}

void CdbOidKey::toBinary(ByteBuffer* out) const {
	out->putInt(this->type);
	this->oid->toBinary(out);
}

void CdbOidKey::fromBinary(ByteBuffer* in) {
	this->oid = CdbOid::fromBinary(in);
}

} /* namespace codablecash */
