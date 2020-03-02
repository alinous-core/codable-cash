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

	switch(leftTypeCode){

	}

	// FIXME type check
	return 0;

}


} /* namespace alinous */
