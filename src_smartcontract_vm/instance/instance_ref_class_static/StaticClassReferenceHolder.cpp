/*
 * StaticClassReferenceHolder.cpp
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#include "instance/instance_ref_class_static/StaticClassReferenceHolder.h"
#include "instance/instance_ref_class_static/StaticClassEntry.h"

#include "instance/instance_ref/VmRootReference.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "base/HashMap.h"
#include "base/ArrayList.h"

#include "engine/sc_analyze/PackageSpace.h"
#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedClass.h"

#include "lang/sc_declare/ClassDeclare.h"
#include "lang/sc_declare/MemberVariableDeclare.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_ref_class_static_meta/StaticClassMetadataHolder.h"
#include "instance/instance_ref_class_static_meta/StaticClassMetadata.h"


namespace alinous {

StaticClassReferenceHolder::StaticClassReferenceHolder() {
	this->classMap = new HashMap<UnicodeString, StaticClassEntry>();

}

StaticClassReferenceHolder::~StaticClassReferenceHolder() {
	Iterator<UnicodeString>* it = this->classMap->keySet()->iterator(); __STP(it);

	while(it->hasNext()){
		const UnicodeString* key = it->next();
		StaticClassEntry* entry = this->classMap->get(key);

		delete entry;
	}

	delete this->classMap;
}

void StaticClassReferenceHolder::init(VirtualMachine* vm, AnalyzeContext* actx) {
	HashMap<UnicodeString, PackageSpace>* spaces = actx->getPackageSpaces();

	Iterator<UnicodeString>* it = spaces->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		PackageSpace* space = spaces->get(key);

		initPackageSpace(vm, actx, space);
	}

	setupIneritClass(vm, actx);
}

void StaticClassReferenceHolder::setupIneritClass(VirtualMachine* vm, AnalyzeContext* actx) {
	Iterator<UnicodeString>* it = this->classMap->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		StaticClassEntry* entry = this->classMap->get(key);

		entry->initParentClasses(this->classMap);
	}
}

void StaticClassReferenceHolder::initPackageSpace(VirtualMachine* vm, AnalyzeContext* actx, PackageSpace* space) {
	HashMap<UnicodeString, AnalyzedClass>* classes = space->getMap();

	Iterator<UnicodeString>* it = classes->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		AnalyzedClass* aclazz = classes->get(key);

		initAnalyzedClass(vm, actx, aclazz);
	}
}

void StaticClassReferenceHolder::initAnalyzedClass(VirtualMachine* vm, AnalyzeContext* actx, AnalyzedClass* aclass) {
	ClassDeclare* dec = aclass->getClassDeclare();
	const UnicodeString* fqn = aclass->getFullQualifiedName();

	VmRootReference* rootRef = vm->getVmRootReference();
	StaticClassEntry* classEntry = getClassEntry(fqn, aclass);

	ArrayList<MemberVariableDeclare>* list = dec->getMemberVariables();
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = list->get(i);

		if(val->isStatic()){
			classEntry->addReference(vm, rootRef, val);
		}
	}

	// meta data
	StaticClassMetadataHolder* holder = actx->getStaticVariableHolder();
	StaticClassMetadata* classMeta = holder->getClassMetadata(fqn);
	assert(classMeta != nullptr);

	classMeta->setClassEntry(classEntry);
}

StaticClassEntry* StaticClassReferenceHolder::getClassEntry(const UnicodeString* fqn, AnalyzedClass* aclass) {
	StaticClassEntry* entry = this->classMap->get(fqn);

	if(entry == nullptr){
		entry = new StaticClassEntry(aclass);
		this->classMap->put(fqn, entry);
	}

	return entry;
}


void StaticClassReferenceHolder::removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept {
	Iterator<UnicodeString>* it = this->classMap->keySet()->iterator(); __STP(it);

	while(it->hasNext()){
		const UnicodeString* key = it->next();
		StaticClassEntry* entry = this->classMap->get(key);

		entry->removeInnerReferences(vm);
	}
}

} /* namespace alinous */
