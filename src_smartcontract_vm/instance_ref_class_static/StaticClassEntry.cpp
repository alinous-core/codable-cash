/*
 * StaticClassEntry.cpp
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#include "instance_ref_class_static/StaticClassEntry.h"

#include "sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"

#include "sc_declare/MemberVariableDeclare.h"

#include "vm/VirtualMachine.h"

#include "instance_ref/RefereceFactory.h"
#include "instance_ref/VmRootReference.h"

#include "instance_ref/AbstractReference.h"

namespace alinous {

StaticClassEntry::StaticClassEntry(AnalyzedClass* aclazz) {
	this->aclazz = aclazz;
	this->members = new HashMap<UnicodeString, AbstractReference>();
}

StaticClassEntry::~StaticClassEntry() {
	this->aclazz = nullptr;

	delete this->members;
}

void StaticClassEntry::addReference(VirtualMachine* vm, VmRootReference* rootRef, MemberVariableDeclare* val) {
	const UnicodeString* name = val->getName();

	AbstractReference* ref = RefereceFactory::createReferenceFromDefinition(rootRef, val, vm);
	this->members->put(name, ref);
}

} /* namespace alinous */
