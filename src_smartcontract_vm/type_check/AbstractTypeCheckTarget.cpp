/*
 * AbstractTypeCheckTarget.cpp
 *
 *  Created on: 2020/03/02
 *      Author: iizuka
 */

#include "type_check/AbstractTypeCheckTarget.h"
#include "sc_expression/AbstractExpression.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"

#include "base/UnicodeString.h"


namespace alinous {

AbstractTypeCheckTarget::AbstractTypeCheckTarget(AbstractExpression* exp) {
	this->exp = exp;
	this->atype = nullptr;
	this->str = nullptr;
}

AbstractTypeCheckTarget::~AbstractTypeCheckTarget() {
	delete this->atype;
	delete this->str;
}

void AbstractTypeCheckTarget::init(AnalyzeContext* actx) {
	AnalyzedType t = this->exp->getType(actx);
	this->atype = new AnalyzedType(t);

}

AnalyzedType* AbstractTypeCheckTarget::getAnalyzedType() const noexcept {
	return this->atype;
}

const UnicodeString* AbstractTypeCheckTarget::toString() noexcept {
	if(this->str == nullptr){
		const UnicodeString* name = this->atype->stringName();
		this->str = new UnicodeString(name);
	}

	return str;
}

} /* namespace alinous */
