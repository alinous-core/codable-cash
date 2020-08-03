/*
 * EqualityScanCondition.cpp
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#include "scan_condition_exp/EqualityScanCondition.h"

#include "sc/CodeElement.h"

#include "scan_condition/IValueProvider.h"

#include "engine/CdbException.h"

#include "base/UnicodeString.h"
using namespace alinous;

namespace codablecash {

EqualityScanCondition::EqualityScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_EQUALITY) {
	this->left = nullptr;
	this->right = nullptr;
	this->str = nullptr;
}

EqualityScanCondition::~EqualityScanCondition() {
	delete this->left;
	delete this->right;
	resetStr();
}

void EqualityScanCondition::setLeft(IValueProvider* element) {
	this->left = element;
	resetStr();
}

void EqualityScanCondition::setRight(IValueProvider* element) {
	this->right = element;
	resetStr();
}

const UnicodeString* EqualityScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"");

		AbstractScanCondition* cond = dynamic_cast<AbstractScanCondition*>(this->left);
		this->str->append(cond->toStringCode());

		this->str->append(L" = ");

		cond = dynamic_cast<AbstractScanCondition*>(this->right);
		this->str->append(cond->toStringCode());
	}

	return this->str;
}

void EqualityScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
