/*
 * ExceptionInstanceFactory.h
 *
 *  Created on: 2020/04/14
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_CLASS_EXCEPTIONINSTANCEFACTORY_H_
#define INSTANCE_EXCEPTION_CLASS_EXCEPTIONINSTANCEFACTORY_H_

#include "engine/sc_analyze/IVmInstanceFactory.h"

namespace alinous {

class ExceptionInstanceFactory : public IVmInstanceFactory {
public:
	static ExceptionInstanceFactory* getInstance() noexcept;
private:
	ExceptionInstanceFactory();
public:
	virtual ~ExceptionInstanceFactory();

	virtual VmClassInstance* createInstance(AnalyzedClass* clazz, VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_CLASS_EXCEPTIONINSTANCEFACTORY_H_ */
