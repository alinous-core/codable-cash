/*
 * CdbOid.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "engine/CdbOid.h"

namespace codablecash {

CdbOid::CdbOid(uint64_t oid) {
	this->oid = oid;
}

CdbOid::~CdbOid() {

}

int CdbOid::hashCode() const {
	return (int)this->oid;
}

int CdbOid::ValueCompare::operator ()(const CdbOid* const _this, const CdbOid* const object) const noexcept {
	return ((int)_this->oid) - ((int)object->oid);
}

} /* namespace codablecash */
