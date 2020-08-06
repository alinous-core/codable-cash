/*
 * InExpressionScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include <scan_condition_exp/InExpressionScanCondition.h>

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_condition/IValueProvider.h"

#include "scan_condition_exp/ExpressionListScanCondition.h"

namespace codablecash {

InExpressionScanCondition::InExpressionScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_IN) {
	this->left = nullptr;
	this->list = nullptr;

	this->str = nullptr;
}

InExpressionScanCondition::~InExpressionScanCondition() {
	delete this->left;
	delete this->list;
	resetStr();
}

void InExpressionScanCondition::setLeft(IValueProvider* cond) noexcept {
	this->left = cond;
	resetStr();
}

void InExpressionScanCondition::setList(ExpressionListScanCondition* list) noexcept {
	this->list = list;
	resetStr();
}

const UnicodeString* InExpressionScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		AbstractScanConditionElement* el = dynamic_cast<AbstractScanConditionElement*>(left);
		this->str->append(el->toStringCode());
		this->str->append(L" IN (");

		this->str->append(this->list->toStringCode());
		this->str->append(L")");
	}

	return this->str;
}

void InExpressionScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
