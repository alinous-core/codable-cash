/*
 * MethodScore.cpp
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#include "engine/sc_analyze_functions/MethodScore.h"
#include "engine/sc_analyze_functions/VTableMethodEntry.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "lang/sc_declare/ArgumentsListDeclare.h"
#include "lang/sc_declare/MethodDeclare.h"

#include "lang/sc_declare/ClassDeclare.h"

#include "engine/sc_analyze/AnalyzedClass.h"
namespace alinous {

MethodScore::MethodScore(VTableMethodEntry* method) {
	this->method = method;
	this->score = 0;
	this->match = false;
}

MethodScore::~MethodScore() {

}

VTableMethodEntry* MethodScore::getEntry() const noexcept {
	return this->method;
}

void MethodScore::eveluate(ArrayList<AnalyzedType>* types) noexcept {
	MethodDeclare* m = this->method->getMethod();
	ArgumentsListDeclare* listDeclare = m->getArguments();
	ArrayList<AnalyzedType>* baseArgs = listDeclare->getArgumentsAnalyzedType();

	int maxLoop = types->size();
	if(baseArgs->size() != maxLoop){
		return;
	}

	for(int i = 0; i != maxLoop; ++i){
		AnalyzedType* baseType = baseArgs->get(i);
		AnalyzedType* type = types->get(i);

		if(!evaluateTypeScore(baseType, type)){
			return;
		}
	}

	this->match = true;
}


bool MethodScore::evaluateTypeScore(AnalyzedType* base,	AnalyzedType* arg) noexcept {
	uint8_t tt = base->getType();

	bool res;
	switch(tt){
	case AnalyzedType::TYPE_OBJECT:
		res = evaluateObjectTypeScore(base, arg);
		break;
	case AnalyzedType::TYPE_DOM:
		res = evaluateDomObjectTypeScore(base, arg);
		break;
	case AnalyzedType::TYPE_BOOL:
		res = evaluateBoolTypeScore(arg);
		break;
	case AnalyzedType::TYPE_BYTE:
		res = evaluateByteTypeScore(arg);
		break;
	case AnalyzedType::TYPE_CHAR:
		res = evaluateCharTypeScore(arg);
		break;
	case AnalyzedType::TYPE_SHORT:
		res = evaluateShortTypeScore(arg);
		break;
	case AnalyzedType::TYPE_LONG:
		res = evaluateLongTypeScore(arg);
		break;
	case AnalyzedType::TYPE_STRING:
		res = evaluateStringTypeScore(arg);
		break;
	case AnalyzedType::TYPE_INT:
	default:
		res = evaluateIntTypeScore(arg);
		break;
	}

	return res;
}


int MethodScore::getScore() const noexcept {
	return this->score;
}

bool MethodScore::isMatch() const noexcept {
	return this->match;
}

bool MethodScore::evaluateObjectTypeScore(AnalyzedType* base, AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	switch(tt){
	case AnalyzedType::TYPE_NULL:
		res = true;
		break;
	case AnalyzedType::TYPE_OBJECT:
		res = doEvaluateObjectTypeScore(base, arg);
		break;
	case AnalyzedType::TYPE_STRING:
	case AnalyzedType::TYPE_BOOL:
	case AnalyzedType::TYPE_BYTE:
	case AnalyzedType::TYPE_CHAR:
	case AnalyzedType::TYPE_SHORT:
	case AnalyzedType::TYPE_LONG:
	case AnalyzedType::TYPE_INT:
	default:
		break;
	}

	return res;
}

bool MethodScore::evaluateDomObjectTypeScore(AnalyzedType* base, AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	if(tt == AnalyzedType::TYPE_NULL || tt == AnalyzedType::TYPE_DOM){
		res = true;
	}

	return res;
}

bool MethodScore::doEvaluateObjectTypeScore(AnalyzedType* base,	AnalyzedType* arg) noexcept {
	AnalyzedClass* baseClass = base->getAnalyzedClass();
	AnalyzedClass* argClass = arg->getAnalyzedClass();

	if(baseClass->equals(argClass)){
		return true;
	}

	if(argClass->hasBaseClass(baseClass)){
		this->score -= -1;
		return true;
	}

	return false;
}

bool MethodScore::evaluateBoolTypeScore(AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	switch(tt){
	case AnalyzedType::TYPE_BOOL:
		res = true;
		break;
	case AnalyzedType::TYPE_OBJECT:
	case AnalyzedType::TYPE_BYTE:
	case AnalyzedType::TYPE_CHAR:
	case AnalyzedType::TYPE_SHORT:
	case AnalyzedType::TYPE_LONG:
	case AnalyzedType::TYPE_STRING:
	case AnalyzedType::TYPE_INT:
	default:
		break;
	}

	return res;
}

bool MethodScore::evaluateByteTypeScore(AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	switch(tt){
	case AnalyzedType::TYPE_BYTE:
		res = true;
		break;
	case AnalyzedType::TYPE_CHAR:
	case AnalyzedType::TYPE_SHORT:
	case AnalyzedType::TYPE_LONG:
	case AnalyzedType::TYPE_INT:
		res = true;
		this->score -= 1;
		break;
	case AnalyzedType::TYPE_OBJECT:
	case AnalyzedType::TYPE_BOOL:
	case AnalyzedType::TYPE_STRING:
	default:
		break;
	}

	return res;
}

bool MethodScore::evaluateCharTypeScore(AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	switch(tt){
	case AnalyzedType::TYPE_CHAR:
		res = true;
		break;
	case AnalyzedType::TYPE_BYTE:
	case AnalyzedType::TYPE_SHORT:
	case AnalyzedType::TYPE_LONG:
	case AnalyzedType::TYPE_INT:
		res = true;
		this->score -= 1;
		break;
	case AnalyzedType::TYPE_OBJECT:
	case AnalyzedType::TYPE_BOOL:
	case AnalyzedType::TYPE_STRING:
	default:
		break;
	}

	return res;
}


bool MethodScore::evaluateShortTypeScore(AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	switch(tt){

	case AnalyzedType::TYPE_BYTE:
	case AnalyzedType::TYPE_CHAR:
	case AnalyzedType::TYPE_LONG:
	case AnalyzedType::TYPE_INT:
		res = true;
		this->score -= 1;
		break;
	case AnalyzedType::TYPE_SHORT:
		res = true;
		break;
	case AnalyzedType::TYPE_OBJECT:
	case AnalyzedType::TYPE_BOOL:
	case AnalyzedType::TYPE_STRING:
	default:
		break;
	}

	return res;
}

bool MethodScore::evaluateIntTypeScore(AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	switch(tt){
	case AnalyzedType::TYPE_BYTE:
	case AnalyzedType::TYPE_CHAR:
	case AnalyzedType::TYPE_SHORT:
	case AnalyzedType::TYPE_LONG:
		res = true;
		this->score -= 1;
		break;
	case AnalyzedType::TYPE_INT:
		res = true;
		break;
	case AnalyzedType::TYPE_OBJECT:
	case AnalyzedType::TYPE_BOOL:
	case AnalyzedType::TYPE_STRING:
	default:
		break;
	}

	return res;
}

bool MethodScore::evaluateLongTypeScore(AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	switch(tt){

	case AnalyzedType::TYPE_BYTE:
	case AnalyzedType::TYPE_CHAR:
	case AnalyzedType::TYPE_SHORT:
	case AnalyzedType::TYPE_INT:
		res = true;
		this->score -= 1;
		break;
	case AnalyzedType::TYPE_LONG:
		res = true;
		break;
	case AnalyzedType::TYPE_OBJECT:
	case AnalyzedType::TYPE_BOOL:
	case AnalyzedType::TYPE_STRING:
	default:
		break;
	}

	return res;
}

bool MethodScore::evaluateStringTypeScore(AnalyzedType* arg) noexcept {
	uint8_t tt = arg->getType();

	bool res = false;
	switch(tt){
	case AnalyzedType::TYPE_STRING:
		res = true;
		break;
	case AnalyzedType::TYPE_OBJECT:
	case AnalyzedType::TYPE_BOOL:
	case AnalyzedType::TYPE_BYTE:
	case AnalyzedType::TYPE_CHAR:
	case AnalyzedType::TYPE_SHORT:
	case AnalyzedType::TYPE_LONG:
	case AnalyzedType::TYPE_INT:
	default:
		break;
	}

	return res;
}

} /* namespace alinous */
