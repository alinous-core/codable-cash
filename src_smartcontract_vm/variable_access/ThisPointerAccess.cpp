/*
 * ThisPointerAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/ThisPointerAccess.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

ThisPointerAccess::ThisPointerAccess() {
	this->type = nullptr;
}

ThisPointerAccess::~ThisPointerAccess() {
	delete this->type;
}

void ThisPointerAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastInst) {
	AnalyzedClass* clazz = actx->getThisClass();

	this->type = new AnalyzedType(clazz);

	// FIXME analyze
}

AnalyzedType* ThisPointerAccess::getAnalyzedType() const noexcept {
	return this->type;
}

} /* namespace alinous */
