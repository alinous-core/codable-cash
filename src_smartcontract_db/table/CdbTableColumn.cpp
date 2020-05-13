/*
 * CdbTableColumn.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "table/CdbTableColumn.h"

#include "engine/CdbOid.h"


namespace codablecash {

CdbTableColumn::CdbTableColumn(uint64_t oid) {
	this->oid = new CdbOid(oid);
}

CdbTableColumn::~CdbTableColumn() {
	delete this->oid;
}

const CdbOid* CdbTableColumn::getOid() const noexcept {
	return this->oid;
}

} /* namespace codablecash */
