/*
 * AbstractScanColumns.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_columns/AbstractScanColumnsTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

AbstractScanColumnsTarget::AbstractScanColumnsTarget() {
	this->asName = nullptr;
}

AbstractScanColumnsTarget::~AbstractScanColumnsTarget() {
	delete this->asName;
}

void AbstractScanColumnsTarget::setAsName(const UnicodeString* asName) noexcept {
	delete this->asName;
	this->asName = new UnicodeString(asName);
}

} /* namespace codablecash */
