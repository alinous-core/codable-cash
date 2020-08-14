/*
 * CdbOidValueListCursor.cpp
 *
 *  Created on: 2020/08/14
 *      Author: iizuka
 */

#include "table_record_value/CdbOidValueListCursor.h"
#include "table_record_value/CdbOidValueList.h"

namespace codablecash {

CdbOidValueListCursor::CdbOidValueListCursor(const CdbOidValueList* list) {
	this->list = list;
	this->pos = 0;
	this->maxCount = list->size();
	this->obj = nullptr;
}

CdbOidValueListCursor::~CdbOidValueListCursor() {
	this->list = nullptr;
	this->obj = nullptr;
}

bool CdbOidValueListCursor::hasNext() noexcept {
	if(this->pos >= this->maxCount){
		return false;
	}

	this->obj = this->list->get(this->pos++);
	return true;
}

const CdbOid* CdbOidValueListCursor::next() const noexcept {
	return this->next();
}

} /* namespace codablecash */
