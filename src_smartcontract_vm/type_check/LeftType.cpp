/*
 * LeftType.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "type_check/LeftType.h"
#include "type_check/RightType.h"

#include "sc_expression/AbstractExpression.h"

#include "type_check/InternalTypeChecker.h"

#include "sc_analyze/AnalyzedType.h"


namespace alinous {

LeftType::LeftType(AbstractExpression* exp) : AbstractTypeCheckTarget(exp) {

}

LeftType::~LeftType() {

}

int LeftType::checkTypeCompatibility(AnalyzeContext* actx, RightType* rightType) {
	AnalyzedType* arightType = rightType->getAnalyzedType();

	return InternalTypeChecker::analyzeCompatibility(this->atype, arightType);
}

} /* namespace alinous */
