/*
 * ColumnIdentifierColumn.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_condition_params/ColumnIdentifierScanParam.h"

namespace codablecash {

ColumnIdentifierScanParam::ColumnIdentifierScanParam(SQLColumnIdentifier* sqlColId) : sqlColId(sqlColId){
	this->cdbColumn = nullptr;
	this->str = nullptr;
}

ColumnIdentifierScanParam::~ColumnIdentifierScanParam() {
	delete this->str;
	delete this->cdbColumn;
}

const UnicodeString* ColumnIdentifierScanParam::toStringCode() noexcept {
	if(this->str == nullptr){
		delete this->str;
		this->str = new UnicodeString(L"");

		const UnicodeString* s = nullptr;
		s = this->sqlColId->getSchema();
		if(s != nullptr){
			this->str->append(L".");
			this->str->append(s);
		}
		s = this->sqlColId->getTableName();
		if(s != nullptr){
			this->str->append(L".");
			this->str->append(s);
		}

		s = this->sqlColId->getColumnName();
		this->str->append(s);
	}

	return this->str;
}


} /* namespace codablecash */
