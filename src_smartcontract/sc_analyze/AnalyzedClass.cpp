/*
 * AnalyzedClass.cpp
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#include "sc_analyze/AnalyzedClass.h"

namespace alinous {

AnalyzedClass::AnalyzedClass(ClassDeclare* clazz) {
	this->clazz = clazz;
}

AnalyzedClass::~AnalyzedClass() {
	this->clazz = nullptr;
}

} /* namespace alinous */
