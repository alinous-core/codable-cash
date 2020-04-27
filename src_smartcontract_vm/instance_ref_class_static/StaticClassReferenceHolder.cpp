/*
 * StaticClassReferenceHolder.cpp
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#include "instance_ref_class_static/StaticClassReferenceHolder.h"

#include "instance_ref_class_static/StaticClassEntry.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "base/HashMap.h"

#include "sc_analyze/PackageSpace.h"
#include "sc_analyze/AnalyzeContext.h"

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
}

void StaticClassReferenceHolder::init(VirtualMachine* vm, AnalyzeContext* actx) {
	HashMap<UnicodeString, PackageSpace>* spaces = actx->getPackageSpaces();

	Iterator<UnicodeString>* it = spaces->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		PackageSpace* space = spaces->get(key);

		initPackageSpace(vm, space);
	}
}

void StaticClassReferenceHolder::initPackageSpace(VirtualMachine* vm, PackageSpace* space) {
	HashMap<UnicodeString, AnalyzedClass>* classes = space->getMap();

	Iterator<UnicodeString>* it = classes->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		AnalyzedClass* aclazz = classes->get(key);

	}
}


void StaticClassReferenceHolder::removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept {
	Iterator<UnicodeString>* it = this->classMap->keySet()->iterator(); __STP(it);

	while(it->hasNext()){
		const UnicodeString* key = it->next();
		StaticClassEntry* entry = this->classMap->get(key);

		// FIXME release ref
	}
}
} /* namespace alinous */
