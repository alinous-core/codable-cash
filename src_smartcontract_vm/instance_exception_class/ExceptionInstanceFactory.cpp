/*
 * ExceptionInstanceFactory.cpp
 *
 *  Created on: 2020/04/14
 *      Author: iizuka
 */

#include "instance_exception_class/ExceptionInstanceFactory.h"

namespace alinous {

ExceptionInstanceFactory::ExceptionInstanceFactory() {

}

ExceptionInstanceFactory::~ExceptionInstanceFactory() {

}

ExceptionInstanceFactory* ExceptionInstanceFactory::getInstance() noexcept {
	static ExceptionInstanceFactory factory;
	return &factory;
}

VmClassInstance* ExceptionInstanceFactory::createInstance(AnalyzedClass* clazz, VirtualMachine* vm) {
	// FIXME instance
}

} /* namespace alinous */
