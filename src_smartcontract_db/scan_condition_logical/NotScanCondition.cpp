/*
 * NotScanCondition.cpp
 *
 *  Created on: 2020/07/29
 *      Author: iizuka
 */

#include "scan_condition_logical/NotScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

using namespace alinous;

namespace codablecash {

NotScanCondition::NotScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_NOT) {
	this->cond = nullptr;
	this->str = nullptr;
}

NotScanCondition::~NotScanCondition() {
	delete this->cond;
	resetStr();
}

bool NotScanCondition::isContainer() const noexcept {
	return true;
}

void NotScanCondition::addCondition(AbstractScanCondition* cond) {
	delete this->cond;
	this->cond = cond;

	resetStr();
}

AbstractScanCondition* NotScanCondition::cloneCondition() const noexcept {
	NotScanCondition* cond = new NotScanCondition();

	cond->addCondition(this->cond->cloneCondition());

	return cond;
}

const UnicodeString* NotScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"NOT ");
		this->str->append(this->cond->toStringCode());
	}

	return this->str;
}

void NotScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
