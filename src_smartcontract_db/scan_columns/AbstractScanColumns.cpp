/*
 * AbstractScanColumns.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_columns/AbstractScanColumns.h"

#include "base/UnicodeString.h"

namespace codablecash {

AbstractScanColumns::AbstractScanColumns() {
	this->asName = nullptr;
}

AbstractScanColumns::~AbstractScanColumns() {
	delete this->asName;
}

void AbstractScanColumns::setAsName(const UnicodeString* asName) noexcept {
	delete this->asName;
	this->asName = new UnicodeString(asName);
}

} /* namespace codablecash */
