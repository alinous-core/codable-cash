/*
 * LeftType.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "vm/type_check/LeftType.h"
#include "vm/type_check/RightType.h"

#include "lang/sc_expression/AbstractExpression.h"

#include "vm/type_check/InternalTypeChecker.h"

#include "engine/sc_analyze/AnalyzedType.h"


namespace alinous {

LeftType::LeftType(AbstractExpression* exp) : AbstractTypeCheckTarget(exp) {

}

LeftType::~LeftType() {

}

int LeftType::checkTypeCompatibility(AnalyzeContext* actx, RightType* rightType, bool compare) {
	AnalyzedType* arightType = rightType->getAnalyzedType();

	if(!compare && arightType->isNull() && (this->atype->isArray() || (!this->atype->isPrimitiveInteger() && !this->atype->isBool()))){
		return InternalTypeChecker::OK;
	}

	return InternalTypeChecker::analyzeCompatibility(this->atype, arightType);
}

} /* namespace alinous */
