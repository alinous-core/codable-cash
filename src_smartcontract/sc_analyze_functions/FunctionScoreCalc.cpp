/*
 * FunctionScoreCalc.cpp
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#include "sc_analyze_functions/FunctionScoreCalc.h"

#include "sc_analyze_functions/MethodScore.h"

namespace alinous {

FunctionScoreCalc::FunctionScoreCalc(VTableClassEntry* classEntry) {
	this->topScore = nullptr;
	this->classEntry = classEntry;
}

FunctionScoreCalc::~FunctionScoreCalc() {
	delete this->topScore;
	this->classEntry = nullptr;
}

} /* namespace alinous */
