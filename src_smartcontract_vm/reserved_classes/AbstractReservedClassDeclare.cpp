/*
 * AbstractReservedClassDeclare.cpp
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#include "reserved_classes/AbstractReservedClassDeclare.h"

#include "sc_declare/MethodDeclare.h"
#include "sc_declare/MemberVariableDeclare.h"

#include "base/ArrayList.h"
#include "base/UnicodeString.h"

#include "sc_declare/AccessControlDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"

#include "sc_statement/StatementBlock.h"


namespace alinous {

AbstractReservedClassDeclare::AbstractReservedClassDeclare() : ClassDeclare() {
	this->methods = new ArrayList<MethodDeclare>();
	this->members = new ArrayList<MemberVariableDeclare>();
}

AbstractReservedClassDeclare::~AbstractReservedClassDeclare() {
	this->methods->deleteElements();
	delete this->methods;

	this->members->deleteElements();
	delete this->members;
}

ArrayList<MethodDeclare>* AbstractReservedClassDeclare::getMethods() noexcept {
	return this->methods;
}

void AbstractReservedClassDeclare::preAnalyze(AnalyzeContext* actx) {
}

void AbstractReservedClassDeclare::analyzeTypeRef(AnalyzeContext* actx) {
}

void AbstractReservedClassDeclare::analyze(AnalyzeContext* actx) {
}

ArrayList<MemberVariableDeclare>* AbstractReservedClassDeclare::getMemberVariables() noexcept {
	return this->members;
}

void AbstractReservedClassDeclare::addDefaultConstructor(const UnicodeString* className) noexcept {
	MethodDeclare* m = new MethodDeclare();
	this->methods->addElement(m);

	AccessControlDeclare* ctrl = new AccessControlDeclare();
	ctrl->setCtrl(AccessControlDeclare::PUBLIC);
	m->setAccessControl(ctrl);

	UnicodeString* name = new UnicodeString(className);
	m->setName(name);

	ArgumentsListDeclare* argDeclare = new ArgumentsListDeclare();
	m->setArguments(argDeclare);

	StatementBlock* block = new StatementBlock();
	m->setBlock(block);
}

} /* namespace alinous */
