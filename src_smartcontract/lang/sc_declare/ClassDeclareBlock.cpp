/*
 * ClassDeclareBlock.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "lang/sc_declare/ClassDeclareBlock.h"
#include "lang/sc_declare/MemberVariableDeclare.h"
#include "lang/sc_declare/MethodDeclare.h"
#include "lang/sc_declare/ArgumentsListDeclare.h"
#include "lang/sc_declare/AccessControlDeclare.h"

#include "vm/VirtualMachine.h"

#include "base/UnicodeString.h"

#include "lang/sc_statement/StatementBlock.h"

namespace alinous {

ClassDeclareBlock::ClassDeclareBlock()  : CodeElement(CodeElement::CLASS_DECLARE_BLOCK) {
}

ClassDeclareBlock::~ClassDeclareBlock() {
	this->methods.deleteElements();
	this->variables.deleteElements();
}


void ClassDeclareBlock::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->variables.size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = this->variables.get(i);
		val->setParent(this);
		val->preAnalyze(actx);
	}

	maxLoop = this->methods.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);
		method->setParent(this);
		method->preAnalyze(actx);
	}
}

void ClassDeclareBlock::addDefaultConstructor(const UnicodeString* className) noexcept {
	// add default constructor
	if(hasDefaultConstructor(className)){
		return;
	}

	MethodDeclare* m = new MethodDeclare();
	this->methods.addElement(m);

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

bool ClassDeclareBlock::hasDefaultConstructor(const UnicodeString* className) const noexcept {
	int maxLoop = this->methods.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);

		const UnicodeString* name = method->getName();
		ArgumentsListDeclare* arguments = method->getArguments();
		int argSize = arguments->getSize();

		if(argSize == 0 && name->equals(className)){
			return true;
		}
	}

	return false;
}

void ClassDeclareBlock::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->variables.size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = this->variables.get(i);
		val->analyzeTypeRef(actx);
	}

	maxLoop = this->methods.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);
		method->analyzeTypeRef(actx);
	}

}

void ClassDeclareBlock::analyze(AnalyzeContext* actx) {
	int maxLoop = this->variables.size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = this->variables.get(i);
		val->analyze(actx);
	}

	maxLoop = this->methods.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);
		method->analyze(actx);
	}
}

void ClassDeclareBlock::init(VirtualMachine* vm) {
	int maxLoop = this->variables.size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = this->variables.get(i);
		val->init(vm);
	}

	maxLoop = this->methods.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);
		method->init(vm);
	}
}

void ClassDeclareBlock::addMethod(MethodDeclare* method) noexcept {
	this->methods.addElement(method);
}

ArrayList<MethodDeclare>* ClassDeclareBlock::getMethods() noexcept {
	return &this->methods;
}

ArrayList<MemberVariableDeclare>* ClassDeclareBlock::getMemberVariables() noexcept {
	return &this->variables;
}

void ClassDeclareBlock::addVariable(MemberVariableDeclare* variable) noexcept {
	this->variables.addElement(variable);
}

int ClassDeclareBlock::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->variables.size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = this->variables.get(i);
		total += val->binarySize();
	}

	total += sizeof(uint32_t);
	maxLoop = this->methods.size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);
		total += method->binarySize();
	}

	return total;
}

void ClassDeclareBlock::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::CLASS_DECLARE_BLOCK);

	uint32_t maxLoop = this->variables.size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = this->variables.get(i);
		val->toBinary(out);
	}

	maxLoop = this->methods.size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = this->methods.get(i);
		method->toBinary(out);
	}
}

void ClassDeclareBlock::fromBinary(ByteBuffer* in) {
	uint32_t maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::MEMBER_VARIABLE_DECLARE);

		MemberVariableDeclare* val = dynamic_cast<MemberVariableDeclare*>(element);
		this->variables.addElement(val);
	}

	maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::METHOD_DECLARE);

		MethodDeclare* method = dynamic_cast<MethodDeclare*>(element);
		this->methods.addElement(method);
	}
}

bool ClassDeclareBlock::hasCtrlStatement() const noexcept {
	return false;
}


} /* namespace alinous */
