/*
 * MethodDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "lang/sc_declare/MethodDeclare.h"
#include "lang/sc_declare/AccessControlDeclare.h"
#include "lang/sc_declare/ArgumentsListDeclare.h"
#include "lang/sc_declare_types/AbstractType.h"
#include "lang/sc_declare/ClassDeclare.h"

#include "lang/sc_statement/StatementBlock.h"
#include "base/UnicodeString.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedClass.h"
#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/ValidationError.h"

#include "engine/sc/exceptions.h"

#include "engine/sc_analyze/AnalyzedThisClassStackPopper.h"

#include "vm/VirtualMachine.h"

#include "vm/stack/MethodArgumentSetupper.h"

namespace alinous {

MethodDeclare::MethodDeclare() : CodeElement(CodeElement::METHOD_DECLARE) {
	this->_static = false;
	this->name = nullptr;
	this->ctrl = nullptr;
	this->type = nullptr;
	this->args = nullptr;
	this->block = nullptr;
	this->atype = nullptr;
	this->callSig = nullptr;
	this->fqn = nullptr;
	this->strName = nullptr;
}

MethodDeclare::~MethodDeclare() {
	delete this->name;
	delete this->ctrl;
	delete this->type;
	delete this->args;
	delete this->block;
	delete this->atype;
	delete this->callSig;
	delete this->fqn;
	delete this->strName;
}


void MethodDeclare::preAnalyze(AnalyzeContext* actx) {
	AnalyzedClass* aclass = actx->getAnalyzedClass(this);
	aclass->addMemberMethodDeclare(this);

	this->args->setParent(this);
	this->args->preAnalyze(actx);

	if(this->block != nullptr){
		this->block->setParent(this);
		this->block->preAnalyze(actx);

		if(isConstructor()){
			this->block->adjustDecalutConstructorCall(actx);
		}
	}
}

void MethodDeclare::analyzeTypeRef(AnalyzeContext* actx) {
	TypeResolver* typeResolver = actx->getTypeResolver();

	if(!isConstructor()){
		if(this->type == nullptr){
			actx->addValidationError(ValidationError::CODE_NO_RETURN_METHOD_VALUE, this, L"Return type of method '{0}()' does not exists.", {this->name});
		}
		else {
			this->atype = typeResolver->resolveType(this, this->type);
			if(this->atype == nullptr){
				actx->addValidationError(ValidationError::CODE_WRONG_TYPE_NAME, this, L"The type '{0}' does not exists.", {this->type->toString()});
			}
		}
	}

	this->args->analyzeTypeRef(actx);

	if(this->block != nullptr){
		// set this pointer on analysis phase
		AnalyzedClass* aclass = actx->getAnalyzedClass(this);
		AnalyzedThisClassStackPopper thisStack(actx, aclass);

		this->block->analyzeTypeRef(actx);
	}
}

void MethodDeclare::analyze(AnalyzeContext* actx) {
	this->args->analyze(actx);

	AnalyzedClass* aclass = actx->getAnalyzedClass(this);
	AnalyzedThisClassStackPopper thisStack(actx, aclass);

	if(this->block != nullptr){
		this->block->analyze(actx);
	}
}

void MethodDeclare::setStatic(bool s) noexcept {
	this->_static = s;
}

void MethodDeclare::setAccessControl(AccessControlDeclare* ctrl) noexcept {
	this->ctrl = ctrl;
}

void MethodDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void MethodDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void MethodDeclare::setArguments(ArgumentsListDeclare* args) noexcept {
	this->args = args;
}

void MethodDeclare::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

StatementBlock* MethodDeclare::getBlock() const noexcept {
	return this->block;
}


bool MethodDeclare::isConstructor() const {
	ClassDeclare* dec = getClassDeclare();
	//if(dec == nullptr){
	//	throw new MulformattedScBinaryException(__FILE__, __LINE__);
	//}

	const UnicodeString* clsName = dec->getName();
	return clsName->equals(this->name);
}

const UnicodeString* MethodDeclare::getName() const noexcept {
	return this->name;
}

const UnicodeString* MethodDeclare::getCallSignature() noexcept {
	if(this->callSig == nullptr){
		this->callSig = new UnicodeString(this->name);
		this->callSig->append(L":");

		const UnicodeString* argStr = this->args->getCallSignature();
		this->callSig->append(argStr);
	}


	return this->callSig;
}

bool MethodDeclare::isStatic() const noexcept {
	return this->_static;
}

ArgumentsListDeclare* MethodDeclare::getArguments() const noexcept {
	return this->args;
}

AnalyzedType* MethodDeclare::getReturnedType() const noexcept {
	return this->atype;
}


int MethodDeclare::binarySize() const {
	checkNotNull(this->name);
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->args);

	int total = sizeof(uint16_t);
	total += sizeof(char);
	total += stringSize(this->name);
	total += this->ctrl->binarySize();
	total += this->type->binarySize();
	total += this->args->binarySize();

	total += sizeof(uint8_t);
	if(this->block != nullptr){
		total += this->block->binarySize();
	}

	return total;
}

void MethodDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->args);

	out->putShort(CodeElement::METHOD_DECLARE);

	out->put(this->_static ? (char)1 : (char)0);
	putString(out, this->name);
	this->ctrl->toBinary(out);
	this->type->toBinary(out);
	this->args->toBinary(out);

	out->put(this->block != nullptr ? (uint8_t)1 : (uint8_t)0);
	if(this->block != nullptr){
		this->block->toBinary(out);
	}

}

void MethodDeclare::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	this->_static = (bl == 1);

	this->name = getString(in);

	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::ACCESS_CONTROL_DECLARE);
	this->ctrl = dynamic_cast<AccessControlDeclare*>(element);

	element = createFromBinary(in);
	checkIsType(element);
	this->type = dynamic_cast<AbstractType*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::ARGUMENTS_LIST_DECLARE);
	this->args = dynamic_cast<ArgumentsListDeclare*>(element);

	bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkKind(element, CodeElement::STMT_BLOCK);
		this->block = dynamic_cast<StatementBlock*>(element);
	}
}

void MethodDeclare::init(VirtualMachine* vm) {
	if(this->block != nullptr){
		this->block->init(vm);
	}
}

void MethodDeclare::interpret(FunctionArguments* args, VirtualMachine* vm) {
	StatementBlock* block = getBlock();

	MethodArgumentSetupper argSetup(args, vm);
	//vm->setFunctionArguments(args);

	block->interpret(vm);
}

const UnicodeString* MethodDeclare::toString() {
	if(this->strName == nullptr){
		this->strName = new UnicodeString(L"");

		if(this->atype != nullptr){
			const UnicodeString* retstr = this->atype->stringName();
			this->strName->append(retstr);
			this->strName->append(L" ");
		}

		ClassDeclare* clazzDec = getClassDeclare();
		const UnicodeString* classFqn = clazzDec->getFullQualifiedName();
		this->strName->append(classFqn);
		this->strName->append(L".");

		this->strName->append(this->name);
		this->strName->append(L"(");

		if(this->args != nullptr){
			const UnicodeString* str = this->args->toString();
			this->strName->append(str);
		}

		this->strName->append(L")");
	}

	return this->strName;
}

} /* namespace alinous */
