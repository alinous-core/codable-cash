/*
 * InExpressionScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include <scan_condition_exp/InExpressionScanCondition.h>

#include "sc/CodeElement.h"

namespace codablecash {

InExpressionScanCondition::InExpressionScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_IN) {

}

InExpressionScanCondition::~InExpressionScanCondition() {

}

} /* namespace codablecash */
