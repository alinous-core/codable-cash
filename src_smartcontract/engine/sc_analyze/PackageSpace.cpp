/*
 * PackageSpace.cpp
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#include "engine/sc_analyze/PackageSpace.h"
#include "engine/sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"

#include "lang/sc_declare/ClassDeclare.h"

#include "base/ArrayList.h"
#include "base/StackRelease.h"

namespace alinous {

PackageSpace::PackageSpace(const UnicodeString* name) {
	if(name == nullptr){
		UnicodeString tmp(L"");
		this->name = new UnicodeString(tmp);
	}
	else{
		this->name = new UnicodeString(*name);
	}

	this->classes = new HashMap<UnicodeString, AnalyzedClass>();
}

PackageSpace::~PackageSpace() {
	delete this->name;

	Iterator<UnicodeString>* it = this->classes->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* n = it->next();
		AnalyzedClass* cls = this->classes->get(n);

		if(!cls->isReserved()){
			delete cls;
		}
	}
	delete it;

	delete this->classes;
}

void PackageSpace::addClassDeclare(ClassDeclare* clazz) noexcept {
	AnalyzedClass* aclazz = new AnalyzedClass(clazz);

	this->classes->put(clazz->getName(), aclazz);
}

void PackageSpace::addClassDeclare(AnalyzedClass* clazz) noexcept {
	this->classes->put(clazz->getClassDeclare()->getName(), clazz);
}

AnalyzedClass* PackageSpace::getClass(const UnicodeString* name) noexcept {
	return this->classes->get(name);
}

void PackageSpace::analyzeClassInheritance(AnalyzeContext* actx) noexcept {
	Iterator<UnicodeString>* it = this->classes->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* n = it->next();
		AnalyzedClass* cls = this->classes->get(n);

		doAnalyzeClassInheritance(cls);
	}

	delete it;
}

void PackageSpace::doAnalyzeClassInheritance(AnalyzedClass* cls) noexcept {
	ArrayList<AnalyzedClass> list;
	list.addElement(cls);

	AnalyzedClass* clazz = cls->getExtends();

	while(clazz != nullptr){
		list.addElement(clazz);
		clazz = clazz->getExtends();
	}

	int maxLoop = list.size();
	int idxCount = 0;
	for(int i = maxLoop - 1; i >= 0; --i){
		clazz = list.get(i);

		int idx = clazz->getInheritIndex();
		assert(idx < 0 || idx == idxCount);

		clazz->setInheritIndex(idxCount);
		idxCount++;
	}
}

void PackageSpace::buildVTables(AnalyzeContext* actx) noexcept {
	Iterator<UnicodeString>* it = this->classes->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* n = it->next();
		AnalyzedClass* cls = this->classes->get(n);

		cls->buildVtable(actx);
	}
}

HashMap<UnicodeString, AnalyzedClass>* PackageSpace::getMap() const noexcept {
	return this->classes;
}



bool PackageSpace::isEmpty() const noexcept {
	return this->classes->isEmpty();
}

} /* namespace alinous */
