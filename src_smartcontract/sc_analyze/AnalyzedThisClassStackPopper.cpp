/*
 * AnalyzedThisClassStackPopper.cpp
 *
 *  Created on: 2020/01/16
 *      Author: iizuka
 */

#include "sc_analyze/AnalyzedThisClassStackPopper.h"
#include "sc_analyze/AnalyzeContext.h"

namespace alinous {

AnalyzedThisClassStackPopper::AnalyzedThisClassStackPopper(AnalyzeContext* actx, AnalyzedClass* thisClass) {
	this->actx = actx;
	this->actx->setThisClass(thisClass);
}

AnalyzedThisClassStackPopper::~AnalyzedThisClassStackPopper() {
	this->actx->popThisClass();
}

} /* namespace alinous */
