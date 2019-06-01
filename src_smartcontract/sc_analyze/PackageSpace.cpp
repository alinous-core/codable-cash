/*
 * PackageSpace.cpp
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#include "sc_analyze/PackageSpace.h"
#include "sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"

#include "sc_declare/ClassDeclare.h"

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
		delete cls;
	}
	delete it;

	delete this->classes;
}

void PackageSpace::addClassDeclare(ClassDeclare* clazz) noexcept {
	AnalyzedClass* aclazz = new AnalyzedClass(clazz);

	this->classes->put(clazz->getName(), aclazz);
}

AnalyzedClass* PackageSpace::getClass(const UnicodeString* name) noexcept {
	return this->classes->get(name);
}

} /* namespace alinous */
