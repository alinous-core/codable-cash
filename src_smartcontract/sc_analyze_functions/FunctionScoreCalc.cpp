/*
 * FunctionScoreCalc.cpp
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#include "sc_analyze_functions/FunctionScoreCalc.h"

#include "sc_analyze_functions/MethodScore.h"
#include "sc_analyze_functions/VTableClassEntry.h"
#include "sc_analyze_functions/VTableMethodEntry.h"
#include "sc_analyze_functions/MethodNameCollection.h"

#include "base/ArrayList.h"


namespace alinous {

FunctionScoreCalc::FunctionScoreCalc(VTableClassEntry* classEntry) {
	this->topScore = nullptr;
	this->classEntry = classEntry;
}

FunctionScoreCalc::~FunctionScoreCalc() {
	delete this->topScore;
	this->classEntry = nullptr;
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
	}

	return this->topScore;
}

} /* namespace alinous */
