/*
 * AnalyzedType.cpp
 *
 *  Created on: 2019/06/11
 *      Author: iizuka
 */

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzedClass.h"

namespace alinous {

AnalyzedType::AnalyzedType(uint8_t type) {
	this->type = type;
	this->aclazz = nullptr;
}

AnalyzedType::AnalyzedType(AnalyzedClass* clazz) {
	this->type = TYPE_OBJECT;
	this->aclazz = clazz;
}

AnalyzedType::AnalyzedType(const AnalyzedType& obj) {
	this->type = obj.type;
	this->aclazz = obj.aclazz;
}

AnalyzedType::AnalyzedType() {
	this->type = TYPE_NULL;
	this->aclazz = nullptr;
}

AnalyzedType::~AnalyzedType() {
	this->aclazz = nullptr;
}

AnalyzedClass* AnalyzedType::getAnalyzedClass() const noexcept {
	return this->aclazz;
}

} /* namespace alinous */
