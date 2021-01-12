/*
 * MultipleValueProvidorScanParam.cpp
 *
 *  Created on: 2021/01/12
 *      Author: iizuka
 */

#include "scan_select/scan_condition/params/MultipleValueProvidorScanParam.h"

#include "scan_select/scan_condition/base/IValueProvider.h"

#include "base/UnicodeString.h"

namespace codablecash {

MultipleValueProvidorScanParam::MultipleValueProvidorScanParam(const MultipleValueProvidorScanParam& inst) {
	this->str = nullptr;
}

MultipleValueProvidorScanParam::MultipleValueProvidorScanParam() {
	this->str = nullptr;
}

MultipleValueProvidorScanParam::~MultipleValueProvidorScanParam() {
	this->list.deleteElements();
	delete this->str;
}

const UnicodeString* MultipleValueProvidorScanParam::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			IValueProvider* vp = this->list.get(i);

			const UnicodeString* s = vp->toStringCode();
			// FIXME　MultipleValueProvidorScanParam::toStringCode()
		}
	}

	return this->str;
}

void MultipleValueProvidorScanParam::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* vp = this->list.get(i);
	}
}

IValueProvider* MultipleValueProvidorScanParam::clone() const noexcept {
	return new MultipleValueProvidorScanParam(*this);
}

} /* namespace codablecash */
