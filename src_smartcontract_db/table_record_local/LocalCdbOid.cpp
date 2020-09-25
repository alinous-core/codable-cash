/*
 * LocalCdbOid.cpp
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#include "table_record_local/LocalCdbOid.h"

namespace codablecash {

LocalCdbOid::LocalCdbOid(const LocalCdbOid& inst) : CdbOid(inst) {
}

LocalCdbOid::LocalCdbOid(uint64_t oid) : CdbOid(oid) {

}

LocalCdbOid::~LocalCdbOid() {

}

uint8_t LocalCdbOid::getTypeCode() const noexcept {
	return CdbOid::CDB_LOCAL_OID;
}

bool LocalCdbOid::isLocal() const noexcept {
	return true;
}

int LocalCdbOid::binarySize() const {
	return CdbOid::binarySize();
}

void LocalCdbOid::toBinary(ByteBuffer* out) const {
	CdbOid::toBinary(out);
}

bool LocalCdbOid::equals(const CdbOid* other) const noexcept {
	return CdbOid::equals(other);
}

int LocalCdbOid::ValueCompare::operator ()(
		const CdbOid* const _this, const CdbOid* const object) const noexcept {
	static CdbOid::ValueCompare comp;

	return comp(_this, object);
}

} /* namespace codablecash */
