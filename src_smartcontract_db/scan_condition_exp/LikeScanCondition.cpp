/*
 * LikeScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_exp/LikeScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

using namespace alinous;

namespace codablecash {

LikeScanCondition::LikeScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_LIKE) {
	this->str = nullptr;
}

LikeScanCondition::~LikeScanCondition() {
	resetStr();
}

const UnicodeString* LikeScanCondition::toStringCode() noexcept {
}

void LikeScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
