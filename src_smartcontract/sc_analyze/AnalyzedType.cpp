/*
 * AnalyzedType.cpp
 *
 *  Created on: 2019/06/11
 *      Author: iizuka
 */

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

AnalyzedType::AnalyzedType(uint8_t type) {
	this->type = type;
}

AnalyzedType::AnalyzedType(const AnalyzedType& obj) {
	this->type = obj.type;
}

AnalyzedType::AnalyzedType() {
	this->type = TYPE_NULL;
}

AnalyzedType::~AnalyzedType() {

}

} /* namespace alinous */
