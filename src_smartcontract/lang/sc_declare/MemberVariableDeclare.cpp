/*
 * MemberVariableDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "lang/sc_declare/MemberVariableDeclare.h"
#include "lang/sc_declare/AccessControlDeclare.h"
#include "lang/sc_declare_types/AbstractType.h"

#include "base/UnicodeString.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedClass.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzedThisClassStackPopper.h"

#include "lang/sc_expression/AbstractExpression.h"

#include "engine/sc_analyze_stack/AnalyzeStackPopper.h"
#include "engine/sc_analyze_stack/AnalyzeStackManager.h"

#include "instance/instance_ref/AbstractReference.h"

#include "engine/sc/exceptions.h"

#include "vm/VirtualMachine.h"

#include "vm/stack/StackPopper.h"

#include "instance/instance_gc/GcManager.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "vm/type_check/AnalyzedTypeChecker.h"
#include "vm/type_check/InternalTypeChecker.h"

namespace alinous {

MemberVariableDeclare::MemberVariableDeclare() : CodeElement(CodeElement::MEMBER_VARIABLE_DECLARE) {
	this->ctrl = nullptr;
	this->type = nullptr;
	this->_static = false;
	this->name = nullptr;
	this->exp = nullptr;
	this->atype = nullptr;
}

MemberVariableDeclare::~MemberVariableDeclare() {
	delete this->ctrl;
	delete this->type;
	delete this->name;
	delete this->exp;
	delete this->atype;
}

void MemberVariableDeclare::preAnalyze(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->setParent(this);
		this->exp->preAnalyze(actx);
	}
}

void MemberVariableDeclare::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->analyzeTypeRef(actx);
	}

	TypeResolver* typeResolver = actx->getTypeResolver();

	assert(this->atype == nullptr);

	this->atype = typeResolver->resolveType(this, this->type);
	if(this->atype == nullptr){
		actx->addValidationError(ValidationError::CODE_WRONG_TYPE_NAME, this, L"The type '{0}' does not exists.", {this->type->toString()});
	}
	else if(this->atype->getType() == AnalyzedType::TYPE_VOID){
		actx->addValidationError(ValidationError::CODE_WRONG_TYPE_NAME, this, L"Cannot use void for type declare.", {});
	}
}

void MemberVariableDeclare::analyze(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		// make top stack
		AnalyzeStackManager* stackMgr = actx->getAnalyzeStackManager();
		AnalyzeStackPopper popper(stackMgr, true);
		stackMgr->addFunctionStack();

		// this ptr
		AnalyzedClass* aclass = actx->getAnalyzedClass(this);
		AnalyzedThisClassStackPopper thispopper(actx, aclass);

		this->exp->analyze(actx);

		AnalyzedTypeChecker checker;
		AnalyzedType exAt = this->exp->getType(actx);
		int result = checker.checkCompatibility(actx, this->atype, &exAt);

		if(result == InternalTypeChecker::INCOMPATIBLE){
			actx->addValidationError(ValidationError::CODE_TYPE_INCOMPATIBLE, this, L"Initial variable is incompatible with variable declare .", {});
		}
	}
}

void MemberVariableDeclare::init(VirtualMachine* vm) {
	if(this->exp != nullptr){
		this->exp->init(vm);
	}
}

void MemberVariableDeclare::onAllocate(VirtualMachine* vm, AbstractReference* ref) {
	if(!this->_static && this->exp != nullptr){
		doOnAllocate(vm, ref);
	}
}

void MemberVariableDeclare::doOnAllocate(VirtualMachine* vm, AbstractReference* ref) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	vm->newStack();
	StackPopper popStack(vm);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	IAbstractVmInstanceSubstance* sub = inst != nullptr ? inst->getInstance() : nullptr;
	vm->setLastElement(this);
	ref->substitute(sub, vm);
}

void MemberVariableDeclare::setAccessControl(AccessControlDeclare* ctrl) noexcept {
	this->ctrl = ctrl;
}

void MemberVariableDeclare::setAccessControl(char ctrl) noexcept {
	this->ctrl = new AccessControlDeclare();
	this->ctrl->setCtrl(ctrl);
}


void MemberVariableDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void MemberVariableDeclare::setStatic(bool s) noexcept {
	this->_static = s;
}

void MemberVariableDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

bool MemberVariableDeclare::isStatic() const noexcept {
	return this->_static;
}

const UnicodeString* MemberVariableDeclare::getName() noexcept {
	return this->name;
}

AbstractType* MemberVariableDeclare::getType() noexcept {
	return this->type;
}

void MemberVariableDeclare::setExp(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

AbstractExpression* MemberVariableDeclare::getExp() const noexcept {
	return this->exp;
}

AnalyzedType MemberVariableDeclare::getAnalyzedType() const noexcept {
	return *this->atype;
}


int MemberVariableDeclare::binarySize() const {
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->name);

	int total = sizeof(uint16_t);

	bool isnull = (this->exp == nullptr);
	total += sizeof(uint8_t);
	if(!isnull){
		total += this->exp->binarySize();
	}

	total += sizeof(uint8_t);
	total += this->ctrl->binarySize();
	total += this->type->binarySize();
	total += stringSize(this->name);

	return total;
}

void MemberVariableDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->name);

	out->putShort(CodeElement::MEMBER_VARIABLE_DECLARE);

	bool isnull = (this->exp == nullptr);
	out->put(isnull ? (char)1 : (char)0);
	if(!isnull){
		this->exp->toBinary(out);
	}

	out->put(this->_static ? (char)1 : (char)0);
	this->ctrl->toBinary(out);
	this->type->toBinary(out);
	putString(out, this->name);
}

void MemberVariableDeclare::fromBinary(ByteBuffer* in) {

	uint8_t bl = in->get();
	if(bl == 0){
		CodeElement* element = createFromBinary(in);
		checkIsExp(element);
		this->exp = dynamic_cast<AbstractExpression*>(element);
	}

	bl = in->get();
	this->_static = (bl == 1);

	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::ACCESS_CONTROL_DECLARE);
	this->ctrl = dynamic_cast<AccessControlDeclare*>(element);

	element = createFromBinary(in);
	checkIsType(element);

	this->type = dynamic_cast<AbstractType*>(element);

	this->name = getString(in);
}
} /* namespace alinous */
