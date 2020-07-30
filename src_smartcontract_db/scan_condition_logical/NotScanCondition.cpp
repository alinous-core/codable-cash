/*
 * NotScanCondition.cpp
 *
 *  Created on: 2020/07/29
 *      Author: iizuka
 */

#include "scan_condition_logical/NotScanCondition.h"

#include "sc/CodeElement.h"

using namespace alinous;

namespace codablecash {

NotScanCondition::NotScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_NOT) {
	this->cond = nullptr;
}

NotScanCondition::~NotScanCondition() {
	delete this->cond;
}

bool NotScanCondition::isContainer() const noexcept {
	return true;
}

void NotScanCondition::addCondition(AbstractScanCondition* cond) {
	delete this->cond;
	this->cond = cond;
}

} /* namespace codablecash */
