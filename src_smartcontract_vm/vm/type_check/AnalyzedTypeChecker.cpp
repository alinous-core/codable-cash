/*
 * AnalyzedTypeChecker.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "vm/type_check/AnalyzedTypeChecker.h"

#include "vm/type_check/LeftType.h"
#include "vm/type_check/RightType.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "lang/sc_expression/AbstractExpression.h"

#include "vm/type_check/InternalTypeChecker.h"

#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"


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
	return checkCompatibility(actx, leftExp, rightExp, false);
}

bool AnalyzedTypeChecker::checkCompatibility(AnalyzeContext* actx, AbstractExpression* leftExp, AbstractExpression* rightExp, bool compare) {
	this->left = new LeftType(leftExp);
	this->left->init(actx);

	this->right = new RightType(rightExp);
	this->right->init(actx);

	int result = this->left->checkTypeCompatibility(actx, this->right, compare);
	if(compare && (result == InternalTypeChecker::INCOMPATIBLE || result == InternalTypeChecker::WARN_PRECISION)){
		result = this->right->checkTypeCompatibility(actx, this->left);
	}

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

int AnalyzedTypeChecker::checkCompatibility(AnalyzeContext* actx, AnalyzedType* leftType, AnalyzedType* rightType) {
	int result = InternalTypeChecker::analyzeCompatibility(leftType, rightType);

	return result;
}

} /* namespace alinous */
