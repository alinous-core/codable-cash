/*
 * AnalyzedThisClassStackPopper.cpp
 *
 *  Created on: 2020/01/16
 *      Author: iizuka
 */

#include "engine/sc_analyze/AnalyzedThisClassStackPopper.h"
#include "engine/sc_analyze/AnalyzeContext.h"

namespace alinous {

AnalyzedThisClassStackPopper::AnalyzedThisClassStackPopper(AnalyzeContext* actx, AnalyzedClass* thisClass) {
	this->actx = actx;
	if(thisClass != nullptr){
		this->actx->setThisClass(thisClass);
	}
}

AnalyzedThisClassStackPopper::~AnalyzedThisClassStackPopper() {
	this->actx->popThisClass();
}

} /* namespace alinous */
