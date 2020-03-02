/*
 * AnalyzedTypeChecker.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "type_check/AnalyzedTypeChecker.h"

#include "type_check/LeftType.h"
#include "type_check/RightType.h"

#include "sc_analyze/AnalyzedType.h"

#include "sc_expression/AbstractExpression.h"

#include "type_check/InternalTypeChecker.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"


namespace alinous {

AnalyzedTypeChecker::AnalyzedTypeChecker() {
	this->left = nullptr;
	this->right = nullptr;
}

AnalyzedTypeChecker::~AnalyzedTypeChecker() {
	delete this->left;
	delete this->right;
}

bool AnalyzedTypeChecker::checkCompatibility(AnalyzeContext* actx, AbstractExpression* leftExp, AbstractExpression* rightExp) {
	this->left = new LeftType(leftExp);
	this->left->init(actx);

	this->right = new RightType(rightExp);
	this->right->init(actx);

	int result = this->left->checkTypeCompatibility(actx, this->right);

	bool ret = true;
	switch(result){
	case InternalTypeChecker::INCOMPATIBLE:
		actx->addValidationError(ValidationError::CODE_TYPE_INCOMPATIBLE, leftExp, L"The member '{0}' and {1} are incompatibe.", {this->left->toString(), this->right->toString()});
		ret = false;
		break;
	case InternalTypeChecker::WARN_PRECISION:
		break;
	default:
		break;
	}

	return ret;
}


} /* namespace alinous */
