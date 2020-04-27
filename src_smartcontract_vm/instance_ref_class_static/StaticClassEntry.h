/*
 * StaticClassEntry.h
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_STATICCLASSENTRY_H_
#define INSTANCE_REF_CLASS_STATIC_STATICCLASSENTRY_H_

#include "base/HashMap.h"

namespace alinous {

class AnalyzedClass;
class VirtualMachine;
class MemberVariableDeclare;
class VmRootReference;
class AbstractReference;
class UnicodeString;

class StaticClassEntry {
public:
	StaticClassEntry(AnalyzedClass* aclazz);
	virtual ~StaticClassEntry();

	void addReference(VirtualMachine* vm, VmRootReference* rootRef, MemberVariableDeclare* val);
private:
	AnalyzedClass* aclazz;
	HashMap<UnicodeString, AbstractReference>* members;

};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_STATICCLASSENTRY_H_ */
