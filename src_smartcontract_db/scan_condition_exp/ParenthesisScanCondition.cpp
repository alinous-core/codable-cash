/*
 * ParenthesisScanCondition.cpp
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#include "scan_condition_exp/ParenthesisScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

using namespace alinous;

namespace codablecash {

ParenthesisScanCondition::ParenthesisScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_NOT) {
	this->cond = nullptr;
	this->str = nullptr;
}

ParenthesisScanCondition::~ParenthesisScanCondition() {
	delete this->cond;
	resetStr();
}

void ParenthesisScanCondition::addCondition(AbstractScanCondition* cond) {
	delete this->cond;
	this->cond = cond;
}

const UnicodeString* ParenthesisScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"(");

		this->str->append(this->cond->toStringCode());

		this->str->append(L")");
	}

	return this->str;
}

void ParenthesisScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
