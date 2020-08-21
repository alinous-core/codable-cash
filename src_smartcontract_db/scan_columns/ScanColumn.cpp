/*
 * ScanColumn.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_columns/ScanColumn.h"

#include "base/UnicodeString.h"

namespace codablecash {

ScanColumn::ScanColumn(const SQLColumnIdentifier* sqlColumnId) {
	this->sqlColumnId = sqlColumnId;
}

ScanColumn::~ScanColumn() {
	this->sqlColumnId = nullptr;
}

const UnicodeString* ScanColumn::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
