/*
 * ParenthesisScanCondition.cpp
 *
 *  Created on: 2020/07/30
 *      Author: iizuka
 */

#include "scan_condition_exp/ParenthesisScanCondition.h"

#include "sc/CodeElement.h"


using namespace alinous;

namespace codablecash {

ParenthesisScanCondition::ParenthesisScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_NOT) {
	this->cond = nullptr;
}

ParenthesisScanCondition::~ParenthesisScanCondition() {
	delete this->cond;
}

void ParenthesisScanCondition::addCondition(AbstractScanCondition* cond) {
	delete this->cond;
	this->cond = cond;
}

} /* namespace codablecash */
