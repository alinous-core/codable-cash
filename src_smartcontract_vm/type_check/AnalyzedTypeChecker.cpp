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

}


} /* namespace alinous */
