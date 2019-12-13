/*
 * MethodScore.cpp
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#include "sc_analyze_functions/MethodScore.h"

#include "sc_analyze_functions/VTableMethodEntry.h"

#include "sc_declare/ArgumentsListDeclare.h"
#include "sc_declare/MethodDeclare.h"

namespace alinous {

MethodScore::MethodScore(VTableMethodEntry* method) {
	this->method = method;
	this->score = 0;
	this->match = false;
}

MethodScore::~MethodScore() {

}

void MethodScore::eveluate(ArrayList<AnalyzedType>* types) noexcept {
	MethodDeclare* m = this->method->getMethod();
	ArgumentsListDeclare* listDeclare = m->getArguments();


	int maxLoop = types->size();
	for(int i = 0; i != maxLoop; ++i){


	}
}

int MethodScore::getScore() const noexcept {
	return this->score;
}

bool MethodScore::isMatch() const noexcept {
	return this->match;
}

} /* namespace alinous */
