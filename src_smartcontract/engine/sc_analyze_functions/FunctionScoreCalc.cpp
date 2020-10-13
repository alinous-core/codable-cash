/*
 * FunctionScoreCalc.cpp
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#include "engine/sc_analyze_functions/FunctionScoreCalc.h"

#include "engine/sc_analyze_functions/MethodScore.h"
#include "engine/sc_analyze_functions/VTableClassEntry.h"
#include "engine/sc_analyze_functions/VTableMethodEntry.h"
#include "engine/sc_analyze_functions/MethodNameCollection.h"

#include "base/ArrayList.h"


namespace alinous {

FunctionScoreCalc::FunctionScoreCalc(VTableClassEntry* classEntry) {
	this->topScore = nullptr;
	this->classEntry = classEntry;
	this->errorCode = 0;
}

FunctionScoreCalc::~FunctionScoreCalc() {
	delete this->topScore;
	this->classEntry = nullptr;
	this->list.deleteElements();
}

MethodScore* FunctionScoreCalc::findMethod(const UnicodeString* methodName, ArrayList<AnalyzedType>* types) noexcept {
	MethodNameCollection* collection = this->classEntry->getMethodEntryCollection(methodName);
	if(collection == nullptr){
		return nullptr;
	}

	const ArrayList<VTableMethodEntry>* list = collection->getList();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		VTableMethodEntry* entry = list->get(i);
		MethodScore* score = new MethodScore(entry);

		score->eveluate(types);
		if(score->isMatch()){
			newScore(score);

			if(this->errorCode != 0){
				return nullptr;
			}
		}
		else{
			delete score;
		}
	}

	return this->topScore;
}

ArrayList<MethodScore>* FunctionScoreCalc::getAmbigousList() noexcept {
	return &this->list;
}

void FunctionScoreCalc::newScore(MethodScore* score) noexcept {
	int sc = score->getScore();
	if(this->topScore == nullptr){
		this->topScore = score;
		return;
	}

	if(this->topScore->getScore() == sc){
		this->errorCode = ERROR_AMBIGOUS;

		this->list.addElement(this->topScore);
		this->list.addElement(score);
		this->topScore = nullptr;

		return;
	}
	else if(this->topScore->getScore() < sc){
		delete this->topScore;
		this->topScore = score;

		return;
	}

	delete score;
}

int FunctionScoreCalc::getErrorCode() const noexcept {
	return this->errorCode;
}

} /* namespace alinous */
