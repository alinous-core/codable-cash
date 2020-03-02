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
	AnalyzedType typeLeft = leftExp->getType(actx);
	AnalyzedType typeRight = rightExp->getType(actx);


}


} /* namespace alinous */
