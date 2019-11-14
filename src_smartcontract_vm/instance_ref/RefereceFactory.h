/*
 * RefereceFactory.h
 *
 *  Created on: 2019/06/09
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_REFERECEFACTORY_H_
#define INSTANCE_REF_REFERECEFACTORY_H_

#include <cstdint>

namespace alinous {
class AbstractReference;
class PrimitiveReference;
class MemberVariableDeclare;
class VirtualMachine;

class RefereceFactory {
public:
	static AbstractReference* createReferenceFromDefinition(MemberVariableDeclare* dec, VirtualMachine* vm);
	static PrimitiveReference* createNumericReference(int64_t value, uint8_t type, VirtualMachine* vm);
private:

};

} /* namespace alinous */

#endif /* INSTANCE_REF_REFERECEFACTORY_H_ */
