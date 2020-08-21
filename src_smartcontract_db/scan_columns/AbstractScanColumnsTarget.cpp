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
	this->str = nullptr;
}

AbstractScanColumnsTarget::~AbstractScanColumnsTarget() {
	delete this->asName;
	resetStr();
}

void AbstractScanColumnsTarget::setAsName(const UnicodeString* asName) noexcept {
	delete this->asName;
	this->asName = new UnicodeString(asName);
}

void AbstractScanColumnsTarget::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
