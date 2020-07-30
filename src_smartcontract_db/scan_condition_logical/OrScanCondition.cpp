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

}

OrScanCondition::~OrScanCondition() {

}

} /* namespace codablecash */
