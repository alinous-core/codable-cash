/*
 * ColumnIdentifierColumn.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_condition_params/ColumnIdentifierScanParam.h"

#include "base/UnicodeString.h"

#include "table/CdbTableColumn.h"

#include "sql_expression/SQLColumnIdentifier.h"

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
			this->str->append(s);
			this->str->append(L".");
		}
		s = this->sqlColId->getTableName();
		if(s != nullptr){
			this->str->append(s);
			this->str->append(L".");
		}

		s = this->sqlColId->getColumnName();
		this->str->append(s);
	}

	return this->str;
}


} /* namespace codablecash */
