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

AnalyzedType::AnalyzedType(const AnalyzedType& obj) {
	this->type = obj.type;
	if(obj.aclazz != nullptr){
		this->aclazz = new AnalyzedClass(*(obj.aclazz));
	}
	else{
		this->aclazz = nullptr;
	}
}

AnalyzedType::AnalyzedType() {
	this->type = TYPE_NULL;
	this->aclazz = nullptr;
}

AnalyzedType::~AnalyzedType() {
	delete this->aclazz;
}

} /* namespace alinous */
