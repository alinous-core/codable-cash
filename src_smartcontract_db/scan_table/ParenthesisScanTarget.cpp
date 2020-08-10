/*
 * ParenthesisScanTarget.cpp
 *
 *  Created on: 2020/08/09
 *      Author: iizuka
 */

#include "scan_table/ParenthesisScanTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

ParenthesisScanTarget::ParenthesisScanTarget() {
	this->inner = nullptr;
}

ParenthesisScanTarget::~ParenthesisScanTarget() {

}

const UnicodeString* ParenthesisScanTarget::toString() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"(");

		this->str->append(this->inner->toString());

		this->str->append(L")");
	}

	return this->str;
}

void ParenthesisScanTarget::setInner(AbstractScanTableTarget* inner) noexcept {
	this->inner = inner;
}

} /* namespace codablecash */
