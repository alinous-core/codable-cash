/*
 * MethodScore.cpp
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#include "sc_analyze_functions/MethodScore.h"

namespace alinous {

MethodScore::MethodScore(VTableMethodEntry* method) {
	this->method = method;
	this->score = 0;
	this->match = false;
}

MethodScore::~MethodScore() {

}

void MethodScore::eveluate(ArrayList<AnalyzedType>* types) noexcept {
}

int MethodScore::getScore() const noexcept {
	return this->score;
}

bool MethodScore::isMatch() const noexcept {
	return this->match;
}

} /* namespace alinous */
