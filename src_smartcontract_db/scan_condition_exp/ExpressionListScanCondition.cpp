/*
 * ExpressionListScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_exp/ExpressionListScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_condition/IValueProvider.h"

namespace codablecash {

ExpressionListScanCondition::ExpressionListScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_EXP_LIST) {
	this->str = nullptr;
}

ExpressionListScanCondition::~ExpressionListScanCondition() {
	this->list.deleteElements();
	resetStr();
}

void ExpressionListScanCondition::addElement(IValueProvider* val) noexcept {
	this->list.addElement(val);
	resetStr();
}

const UnicodeString* ExpressionListScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			IValueProvider* vp = this->list.get(i);
			AbstractScanConditionElement* el = dynamic_cast<AbstractScanConditionElement*>(vp);

			if(i > 0){
				this->str->append(L", ");
			}

			this->str->append(el->toStringCode());
		}
	}

	return this->str;
}

void ExpressionListScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
