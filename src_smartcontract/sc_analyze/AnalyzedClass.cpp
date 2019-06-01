/*
 * AnalyzedClass.cpp
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#include "sc_analyze/AnalyzedClass.h"

#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/MethodDeclare.h"

#include "base/UnicodeString.h"

namespace alinous {

AnalyzedClass::AnalyzedClass(ClassDeclare* clazz) {
	this->clazz = clazz;
	this->variables = new HashMap<UnicodeString, MemberVariableDeclare>();
	this->constructors = new HashMap<UnicodeString, MethodDeclare>();
	this->methods = new HashMap<UnicodeString, MethodDeclare>();
}

AnalyzedClass::~AnalyzedClass() {
	this->clazz = nullptr;
	delete this->variables;
}

void AnalyzedClass::addMemberVariableDeclare(MemberVariableDeclare* member) {
	this->variables->put(member->getName(), member);

}

void AnalyzedClass::addMemberMethodDeclare(MethodDeclare* method) {
	if(method->isConstructor()){
		this->constructors->put(method->getName(), method);
		return;
	}

	this->methods->put(method->getName(), method);
}


} /* namespace alinous */
