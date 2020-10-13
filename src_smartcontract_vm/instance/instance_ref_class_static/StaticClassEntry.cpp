/*
 * StaticClassEntry.cpp
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#include "instance/instance_ref_class_static/StaticClassEntry.h"

#include "engine/sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "lang/sc_declare/MemberVariableDeclare.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_ref/RefereceFactory.h"
#include "instance/instance_ref/VmRootReference.h"
#include "instance/instance_ref/AbstractReference.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "lang/sc_expression/AbstractExpression.h"

#include "vm/stack/StackPopper.h"


namespace alinous {

StaticClassEntry::StaticClassEntry(AnalyzedClass* aclazz) {
	this->aclazz = aclazz;
	this->members = new HashMap<UnicodeString, AbstractReference>();
	this->parent = nullptr;
}

StaticClassEntry::~StaticClassEntry() {
	this->aclazz = nullptr;

	Iterator<UnicodeString>* it = this->members->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		AbstractReference* ref = this->members->get(key);

		delete ref;
	}

	delete this->members;
	this->parent = nullptr;
}

void StaticClassEntry::addReference(VirtualMachine* vm, VmRootReference* rootRef, MemberVariableDeclare* val) {
	const UnicodeString* name = val->getName();

	AbstractReference* ref = RefereceFactory::createReferenceFromDefinition(rootRef, val, vm);
	if(ref->isPrimitive()){
		ref->setOwner(rootRef);
	}

	this->members->put(name, ref);
	this->list.addElement(ref);

	AbstractExpression* exp = val->getExp();
	if(exp != nullptr){
		execInitialExpression(vm, ref, exp);
	}
}

AbstractReference* StaticClassEntry::getReferenceByIndex(int index) const noexcept {
	return this->list.get(index);
}

void StaticClassEntry::execInitialExpression(VirtualMachine* vm, AbstractReference* ref, AbstractExpression* exp) {
	GcManager* gc = vm->getGc();

	vm->newStack();
	StackPopper popStack(vm);

	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = exp->interpret(vm);
	releaser.registerInstance(inst);

	vm->setLastElement(exp);
	ref->substitute(inst != nullptr ? inst->getInstance() : nullptr, vm);
}

void StaticClassEntry::initParentClasses(HashMap<UnicodeString, StaticClassEntry>* classesMap) {
	AnalyzedClass* parent = this->aclazz->getExtends();
	if(parent != nullptr){
		const UnicodeString* fqn = parent->getFullQualifiedName();
		StaticClassEntry* ent = classesMap->get(fqn);

		this->parent = ent;
	}

	const ArrayList<AnalyzedClass>* iflist = this->aclazz->getImplements();
	int maxLoop = iflist->size();
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedClass* ifclazz = iflist->get(i);
		const UnicodeString* fqn = ifclazz->getFullQualifiedName();
		StaticClassEntry* ent = classesMap->get(fqn);

		this->interfaces.addElement(ent);
	}
}


void StaticClassEntry::removeInnerReferences(VirtualMachine* vm) noexcept {
	GcManager* gc = vm->getGc();

	Iterator<UnicodeString>* it = this->members->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		AbstractReference* ref = this->members->get(key);

		gc->removeObject(ref);
	}
}

} /* namespace alinous */
