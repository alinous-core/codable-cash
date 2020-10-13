/*
 * RightType.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "vm/type_check/RightType.h"

#include "lang/sc_expression/AbstractExpression.h"

#include "vm/type_check/LeftType.h"
#include "vm/type_check/InternalTypeChecker.h"


namespace alinous {

RightType::RightType(AbstractExpression* exp) : AbstractTypeCheckTarget(exp) {

}

RightType::~RightType() {

}

int RightType::checkTypeCompatibility(AnalyzeContext* actx,	LeftType* leftType) {
	AnalyzedType* aleftType = leftType->getAnalyzedType();

	return InternalTypeChecker::analyzeCompatibility(this->atype, aleftType);
}

} /* namespace alinous */
