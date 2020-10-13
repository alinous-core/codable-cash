/*
 * IVmInstanceFactory.h
 *
 *  Created on: 2020/04/13
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_IVMINSTANCEFACTORY_H_
#define SC_ANALYZE_IVMINSTANCEFACTORY_H_

namespace alinous {

class AnalyzedClass;
class VirtualMachine;
class VmClassInstance;

class IVmInstanceFactory {
public:
	IVmInstanceFactory();
	virtual ~IVmInstanceFactory();

	virtual VmClassInstance* createInstance(AnalyzedClass* clazz, VirtualMachine* vm) = 0;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_IVMINSTANCEFACTORY_H_ */
