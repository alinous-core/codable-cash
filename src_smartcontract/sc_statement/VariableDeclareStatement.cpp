/*
 * VariableDeclareStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement/VariableDeclareStatement.h"

#include "sc_declare_types/AbstractType.h"
#include "sc_expression/VariableIdentifier.h"
#include "sc_expression/AbstractExpression.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzedType.h"

#include "sc_analyze_stack/AnalyzeStack.h"
#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze_stack/AnalyzedStackReference.h"

#include "stack/VmStack.h"

#include "instance_ref/RefereceFactory.h"

#include "instance_gc/GcManager.h"
namespace alinous {

VariableDeclareStatement::VariableDeclareStatement() : AbstractStatement(CodeElement::STMT_VARIABLE_DECLARE) {
	this->type =nullptr;
	this->variableId = nullptr;
	this->exp = nullptr;
	this->atype = nullptr;
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
	}

	this->atype = resolver->resolveType(this, this->type);
	AnalyzeStack* stack = stackManager->top();


	const UnicodeString* strName = this->variableId->getName();
	AnalyzedStackReference* ref = new AnalyzedStackReference(strName, this->atype);
	stack->addVariableDeclare(ref);
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

	AbstractReference* ref = RefereceFactory::createReferenceFromAnalyzedType(this->atype, vm);
	stack->addInnerReference(ref);

	if(this->exp != nullptr){
		AbstractVmInstance* instValue = this->exp->interpret(vm);
		ref->substitute(instValue, vm);

		gc->handleFloatingObject(instValue);
	}
}

} /* namespace alinous */
