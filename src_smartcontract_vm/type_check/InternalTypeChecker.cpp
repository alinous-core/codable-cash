/*
 * InternalTypeChecker.cpp
 *
 *  Created on: 2020/03/02
 *      Author: iizuka
 */

#include <cstdint>

#include "type_check/InternalTypeChecker.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {


int InternalTypeChecker::analyzeCompatibility(AnalyzedType* leftType, AnalyzedType* rightType) {
	uint8_t leftTypeCode = leftType->getType();
	int dim = leftType->getDim();

	if(dim != rightType->getDim()){
		return INCOMPATIBLE;
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
	default:
		break;
	}

	return retcode;

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

	// FIXME inheritance

	return OK;
}

int InternalTypeChecker::checkString(AnalyzedType* leftType, AnalyzedType* rightType) {
	uint8_t rightTypeCode = rightType->getType();
	if(rightTypeCode == AnalyzedType::TYPE_STRING){
		return OK;
	}

	return INCOMPATIBLE;
}

int InternalTypeChecker::checkPrimitive(AnalyzedType* leftType,	AnalyzedType* rightType) {
	uint8_t leftTypeCode = leftType->getType();
	uint8_t rightTypeCode = rightType->getType();

	if(!rightType->isPrimitiveInteger()){
		return INCOMPATIBLE;
	}

	if(leftTypeCode < rightTypeCode){
		return WARN_PRECISION;
	}

	return OK;
}

} /* namespace alinous */
