/*
 * PackageSpace.cpp
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#include "sc_analyze/PackageSpace.h"
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

	this->classes = new HashMap<UnicodeString, ClassDeclare>();
}

PackageSpace::~PackageSpace() {
	delete this->name;
	delete this->classes;
}

void PackageSpace::addClassDeclare(ClassDeclare* clazz) noexcept {
	this->classes->put(clazz->getName(), clazz);
}

ClassDeclare* PackageSpace::getClass(const UnicodeString* name) noexcept {
	return this->classes->get(name);
}

} /* namespace alinous */
