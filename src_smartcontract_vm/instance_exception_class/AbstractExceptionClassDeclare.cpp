/*
 * AbstractExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/18
 *      Author: iizuka
 */

#include "instance_exception_class/AbstractExceptionClassDeclare.h"

#include "sc_analyze/AnalyzedClass.h"
namespace alinous {

AbstractExceptionClassDeclare::AbstractExceptionClassDeclare() : AbstractReservedClassDeclare() {
	this->aclass = nullptr;
}

AbstractExceptionClassDeclare::~AbstractExceptionClassDeclare() {

}

void AbstractExceptionClassDeclare::setAnalyzedClass(AnalyzedClass* aclass) noexcept {
	this->aclass = aclass;
}

} /* namespace alinous */
