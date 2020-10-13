/*
 * VariableDeclareStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_statement/VariableDeclareStatement.h"

#include "lang/sc_declare_types/AbstractType.h"
#include "lang/sc_expression/VariableIdentifier.h"
#include "lang/sc_expression/AbstractExpression.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "engine/sc_analyze_stack/AnalyzeStack.h"
#include "engine/sc_analyze_stack/AnalyzeStackManager.h"
#include "engine/sc_analyze_stack/AnalyzedStackReference.h"

#include "vm/stack/VmStack.h"

#include "instance_ref/RefereceFactory.h"

#include "instance_gc/GcManager.h"
#include "instance_gc/StackFloatingVariableHandler.h"

#include "instance_exception/ExceptionInterrupt.h"

#include "vm/type_check/AnalyzedTypeChecker.h"

#include "engine/sc_analyze/ValidationError.h"

#include "vm/type_check/InternalTypeChecker.h"
namespace alinous {

VariableDeclareStatement::VariableDeclareStatement() : AbstractStatement(CodeElement::STMT_VARIABLE_DECLARE) {
	this->type =nullptr;
	this->variableId = nullptr;
	this->exp = nullptr;
	this->atype = nullptr;
	this->bctrl = false;
}

VariableDeclareStatement::~VariableDeclareStatement() {
	delete this->type;
	delete this->variableId;
	delete this->exp;
	delete this->atype;
}

void VariableDeclareStatement::preAnalyze(AnalyzeContext* actx) {
	this->type->setParent(this);
	this->variableId->setParent(this);
	this->variableId->preAnalyze(actx);

	if(this->exp != nullptr){
		this->exp->setParent(this);
		this->exp->preAnalyze(actx);
	}
}

void VariableDeclareStatement::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->analyzeTypeRef(actx);
	}
}

void VariableDeclareStatement::analyze(AnalyzeContext* actx) {
	TypeResolver* resolver = actx->getTypeResolver();
	AnalyzeStackManager* stackManager = actx->getAnalyzeStackManager();

	if(this->exp != nullptr){
		this->exp->analyze(actx);
		this->bctrl = this->exp->throwsException();
	}

	this->atype = resolver->resolveType(this, this->type);
	if(this->atype == nullptr){
		actx->addValidationError(ValidationError::CODE_TYPE_DOES_NOT_EXISTS, this, L"Declared type does not exists.", {});

		return;
	}

	AnalyzeStack* stack = stackManager->top();

	const UnicodeString* strName = this->variableId->getName();
	AnalyzedStackReference* ref = new AnalyzedStackReference(strName, this->atype);
	stack->addVariableDeclare(ref);

	if(this->exp != nullptr){
		AnalyzedTypeChecker checker;
		AnalyzedType exAt = this->exp->getType(actx);
		int result = checker.checkCompatibility(actx, this->atype, &exAt);

		if(result == InternalTypeChecker::INCOMPATIBLE){
			actx->addValidationError(ValidationError::CODE_TYPE_INCOMPATIBLE, this, L"Initial variable is incompatible with variable declare .", {});
		}
	}
}

void VariableDeclareStatement::setType(AbstractType* type) noexcept {
	this->type = type;
}

void VariableDeclareStatement::setVariableId(VariableIdentifier* variableId) noexcept {
	this->variableId = variableId;
}

void VariableDeclareStatement::setInitExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int VariableDeclareStatement::binarySize() const {
	checkNotNull(this->type);
	checkNotNull(this->variableId);
//	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->type->binarySize();
	total += this->variableId->binarySize();

	bool isNull = (this->exp == nullptr);
	total += 1;

	if(!isNull){
		total += this->exp->binarySize();
	}

	return total;
}

void VariableDeclareStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->type);
	checkNotNull(this->variableId);
	//checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_VARIABLE_DECLARE);
	this->type->toBinary(out);
	this->variableId->toBinary(out);

	bool isNull = (this->exp == nullptr);
	char bl = isNull ? 0 : 1;
	out->put(bl);

	if(!isNull){
		this->exp->toBinary(out);
	}
}

void VariableDeclareStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsType(element);
	this->type = dynamic_cast<AbstractType*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_VARIABLE_ID);
	this->variableId = dynamic_cast<VariableIdentifier*>(element);

	char bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkIsExp(element);
		this->exp = dynamic_cast<AbstractExpression*>(element);
	}
}

void VariableDeclareStatement::init(VirtualMachine* vm) {
	if(this->exp != nullptr){
		this->exp->init(vm);
	}
}

void VariableDeclareStatement::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	VmStack* stack = vm->topStack();

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(stack, this->atype, vm);
	stack->addInnerReference(ref);

	if(this->exp != nullptr){
		StackFloatingVariableHandler releaser(gc);

		AbstractVmInstance* instValue = nullptr;
		try{
			instValue = this->exp->interpret(vm);
			releaser.registerInstance(instValue);
		}
		catch(ExceptionInterrupt* e){
			delete e;
			return;
		}

		vm->setLastElement(this);
		ref->substitute(instValue != nullptr ? instValue->getInstance() : nullptr, vm);
	}
}

bool VariableDeclareStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
}

AnalyzedType VariableDeclareStatement::getType() const noexcept {
	return *this->atype;
}

} /* namespace alinous */
