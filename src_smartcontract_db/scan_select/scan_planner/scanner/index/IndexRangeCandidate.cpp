/*
 * IndexRangeCandidate.cpp
 *
 *  Created on: 2020/11/16
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/IndexRangeCandidate.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "base/UnicodeString.h"

namespace codablecash {

IndexRangeCandidate::IndexRangeCandidate() : IndexCandidate(IndexType::RANGE) {
	this->topValue = nullptr;
	this->bottomEq = false;
	this->topEq = false;
}

IndexRangeCandidate::~IndexRangeCandidate() {
	this->topValue = nullptr;
}

const UnicodeString* IndexRangeCandidate::toCodeString() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		IValueProvider* vp = const_cast<IValueProvider*>(this->value);
		const UnicodeString* s = vp->toStringCode();

		this->str->append(s);

		if(this->bottomEq){
			this->str->append(L" <= ");
		}
		else {
			this->str->append(L" < ");
		}

		ColumnIdentifierScanParam* param = const_cast<ColumnIdentifierScanParam*>(this->column);

		s = param->toStringCode();
		this->str->append(s);

		if(this->topEq){
			this->str->append(L" <= ");
		}
		else {
			this->str->append(L" < ");
		}

		// top value
		vp = const_cast<IValueProvider*>(this->topValue);
		s = vp->toStringCode();

		this->str->append(s);
	}

	return this->str;
}

} /* namespace codablecash */
