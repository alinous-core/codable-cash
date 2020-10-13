/*
 * ExceptionInstanceFactory.cpp
 *
 *  Created on: 2020/04/14
 *      Author: iizuka
 */

#include "instance/instance_exception_class/ExceptionInstanceFactory.h"
#include "instance/instance_exception_class/VmExceptionInstance.h"


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
	VmExceptionInstance* inst = new(vm) VmExceptionInstance(clazz, vm);

	return inst;
}

} /* namespace alinous */
