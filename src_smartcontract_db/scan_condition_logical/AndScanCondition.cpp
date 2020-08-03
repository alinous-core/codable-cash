/*
 * AndScanCondition.cpp
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#include "scan_condition_logical/AndScanCondition.h"

#include "sc/CodeElement.h"


using namespace alinous;

namespace codablecash {

AndScanCondition::AndScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_AND) {
	this->str = nullptr;
}

AndScanCondition::~AndScanCondition() {
	this->list.deleteElements();
	resetStr();
}

void AndScanCondition::addCondition(AbstractScanCondition* cond) {
	this->list.addElement(cond);
	resetStr();
}

const UnicodeString* AndScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanCondition* cond = this->list.get(i);

			if(i != 0){
				this->str->append(L" AND ");
			}

			this->str->append(cond->toStringCode());
		}
	}

	return this->str;
}

void AndScanCondition::resetStr() {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
