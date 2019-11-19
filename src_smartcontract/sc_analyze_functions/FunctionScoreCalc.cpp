/*
 * FunctionScoreCalc.cpp
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#include "sc_analyze_functions/FunctionScoreCalc.h"

#include "sc_analyze_functions/MethodScore.h"

namespace alinous {

FunctionScoreCalc::FunctionScoreCalc() {
	this->topScore = nullptr;
}

FunctionScoreCalc::~FunctionScoreCalc() {
	delete this->topScore;
}

} /* namespace alinous */
