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

}

AndScanCondition::~AndScanCondition() {

}

} /* namespace codablecash */
