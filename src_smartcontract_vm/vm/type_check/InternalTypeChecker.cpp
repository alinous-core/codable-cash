/*
 * InternalTypeChecker.cpp
 *
 *  Created on: 2020/03/02
 *      Author: iizuka
 */

#include <cstdint>

#include "vm/type_check/InternalTypeChecker.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "lang/sc_declare/ClassDeclare.h"
#include "engine/sc_analyze/AnalyzedClass.h"

namespace alinous {


int InternalTypeChecker::analyzeCompatibility(AnalyzedType* leftType, AnalyzedType* rightType) {
	uint8_t leftTypeCode = leftType->getType();
	int dim = leftType->getDim();

	if(!rightType->isNull() && dim != rightType->getDim()){
		return INCOMPATIBLE;
	}

	if(rightType->isNull()){
		return checkRightNull(leftType, rightType);
	}

	int retcode = NO_CHECK;
	switch(leftTypeCode){
	case AnalyzedType::TYPE_BOOL:
		retcode = checkBool(leftType, rightType);
		break;
	case AnalyzedType::TYPE_BYTE:
	case AnalyzedType::TYPE_CHAR:
	case AnalyzedType::TYPE_SHORT:
	case AnalyzedType::TYPE_INT:
	case AnalyzedType::TYPE_LONG:
		retcode = checkPrimitive(leftType, rightType);
		break;
	case AnalyzedType::TYPE_STRING:
		retcode = checkString(leftType, rightType);
		break;
	case AnalyzedType::TYPE_OBJECT:
		retcode = checkObject(leftType, rightType);
		break;
	case AnalyzedType::TYPE_DOM:
		retcode = checkDomObject(leftType, rightType);
		break;
	case AnalyzedType::TYPE_DOM_VALUE:
		retcode = checkDomValue(leftType, rightType);
		break;
	default:
		break;
	}

	return retcode;
}


int InternalTypeChecker::checkDomValue(AnalyzedType* leftType, AnalyzedType* rightType) {
	uint8_t rightTypeCode = rightType->getType();

	if(rightTypeCode == AnalyzedType::TYPE_DOM ||
			rightTypeCode == AnalyzedType::TYPE_DOM_ARRAY ||
			rightTypeCode == AnalyzedType::TYPE_DOM_VALUE ||
			rightTypeCode == AnalyzedType::TYPE_STRING || rightType->isNull() || rightType->isBool() || rightType->isPrimitiveInteger()){
		return OK;
	}

	return INCOMPATIBLE;
}

int InternalTypeChecker::checkDomObject(AnalyzedType* leftType,	AnalyzedType* rightType) {
	uint8_t rightTypeCode = rightType->getType();

	if(rightTypeCode == AnalyzedType::TYPE_DOM || rightTypeCode == AnalyzedType::TYPE_DOM_ARRAY
			|| rightTypeCode == AnalyzedType::TYPE_DOM_VALUE){
		return OK;
	}

	return INCOMPATIBLE;
}


int InternalTypeChecker::checkRightNull(AnalyzedType* leftType, AnalyzedType* rightType) {
	if((!leftType->isPrimitiveInteger() && !leftType->isBool()) || leftType->isArray()){
		return OK;
	}

	return INCOMPATIBLE;
}

int InternalTypeChecker::checkBool(AnalyzedType* leftType, AnalyzedType* rightType) {
	uint8_t rightTypeCode = rightType->getType();
	if(rightTypeCode == AnalyzedType::TYPE_BOOL){
		return OK;
	}

	return INCOMPATIBLE;
}

int InternalTypeChecker::checkObject(AnalyzedType* leftType, AnalyzedType* rightType) {
	uint8_t rightTypeCode = rightType->getType();
	if(rightTypeCode != AnalyzedType::TYPE_OBJECT){
		return INCOMPATIBLE;
	}

	AnalyzedClass* leftClass = leftType->getAnalyzedClass();
	AnalyzedClass* rightClass = rightType->getAnalyzedClass();

	bool result = rightClass->hasBaseClass(leftClass);
	if(!result){
		return INCOMPATIBLE;
	}

	return OK;
}

int InternalTypeChecker::checkString(AnalyzedType* leftType, AnalyzedType* rightType) {
	uint8_t rightTypeCode = rightType->getType();
	if(rightTypeCode == AnalyzedType::TYPE_STRING || rightTypeCode == AnalyzedType::TYPE_DOM_VALUE){
		return OK;
	}

	return INCOMPATIBLE;
}

int InternalTypeChecker::checkPrimitive(AnalyzedType* leftType,	AnalyzedType* rightType) {
	uint8_t leftTypeCode = leftType->getType();
	uint8_t rightTypeCode = rightType->getType();

	if(rightTypeCode == AnalyzedType::TYPE_DOM_VALUE){
		return OK;
	}

	if(!rightType->isPrimitiveInteger()){
		return INCOMPATIBLE;
	}

	if(leftTypeCode < rightTypeCode){
		return WARN_PRECISION;
	}

	return OK;
}

} /* namespace alinous */
