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
#include "sc_declare/ClassExtends.h"

#include "sc_statement/StatementBlock.h"

#include "sc_analyze/PackageSpace.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedClass.h"

#include "reserved_classes/ReservedClassRegistory.h"

#include "sc/CompilationUnit.h"


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
	if(this->extends != nullptr){
		this->extends->setParent(this);
		this->extends->preAnalyze(actx);
	}

	int maxLoop = this->methods->size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods->get(i);

		method->setParent(this);
		method->preAnalyze(actx);
	}

	maxLoop = this->members->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* member = this->members->get(i);

		member->setParent(this);
		member->preAnalyze(actx);
	}
}

void AbstractReservedClassDeclare::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->extends != nullptr){
		this->extends->analyzeTypeRef(actx);
	}

	int maxLoop = this->methods->size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods->get(i);

		method->analyzeTypeRef(actx);
	}

	maxLoop = this->members->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* member = this->members->get(i);

		member->analyzeTypeRef(actx);
	}

	ReservedClassRegistory* reg = ReservedClassRegistory::getInstance();
	CompilationUnit* unit = reg->getUnit();
	PackageSpace* space = actx->getPackegeSpace(unit->getPackageName());

	const UnicodeString* fqn = getFullQualifiedName();
	AnalyzedClass* dec = space->getClass(fqn);

	// set analyzed class
	if(this->extends != nullptr){
		AnalyzedType* cls = this->extends->getAnalyzedType();
		dec->setExtends(cls->getAnalyzedClass());
	}
}

void AbstractReservedClassDeclare::analyze(AnalyzeContext* actx) {
	int maxLoop = this->methods->size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods->get(i);

		method->analyze(actx);
	}

	maxLoop = this->members->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* member = this->members->get(i);

		member->analyze(actx);
	}
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
