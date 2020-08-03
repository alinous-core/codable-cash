/*
 * OrScanCondition.cpp
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#include "scan_condition_logical/OrScanCondition.h"

#include "sc/CodeElement.h"


using namespace alinous;

namespace codablecash {

OrScanCondition::OrScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_OR) {
	this->str = nullptr;
}

OrScanCondition::~OrScanCondition() {
	this->list.deleteElements();
	resetStr();
}

void OrScanCondition::addCondition(AbstractScanCondition* cond) {
	this->list.addElement(cond);
	resetStr();
}

const UnicodeString* OrScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanCondition* cond = this->list.get(i);

			if(i != 0){
				this->str->append(L" OR ");
			}

			this->str->append(cond->toStringCode());
		}
	}

	return this->str;
}

void OrScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
