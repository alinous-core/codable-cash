/*
 * StatementBlock.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "lang/sc_statement/StatementBlock.h"

#include "lang/sc_declare/MethodDeclare.h"
#include "lang/sc_declare/ArgumentsListDeclare.h"
#include "lang/sc_declare/ArgumentDeclare.h"
#include "lang/sc_declare/ClassExtends.h"
#include "lang/sc_declare/ClassDeclare.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "engine/sc_analyze_stack/AnalyzeStackManager.h"
#include "engine/sc_analyze_stack/AnalyzeStackPopper.h"
#include "engine/sc_analyze_stack/AnalyzedStackReference.h"
#include "engine/sc_analyze_stack/AnalyzeStack.h"
#include "engine/sc_analyze/ValidationError.h"

#include "base/StackRelease.h"

#include "vm/stack/StackPopper.h"
#include "vm/stack/VmStack.h"

#include "instance/instance_ref/ObjectReference.h"

#include "vm/variable_access/FunctionArguments.h"

#include "vm/vm_ctrl/BlockState.h"
#include "vm/vm_ctrl/ExecControlManager.h"

#include "vm/vm_ctrl/AbstractCtrlInstruction.h"

#include "lang/sc_statement/ExpressionStatement.h"

#include "lang/sc_expression/FunctionCallExpression.h"
#include "lang/sc_expression/VariableIdentifier.h"


namespace alinous {

StatementBlock::StatementBlock() : AbstractStatement(CodeElement::STMT_BLOCK) {
	this->blockState = nullptr;
	this->bctrl = false;
	this->autoConstructor = nullptr;
}

StatementBlock::~StatementBlock() {
	this->statements.deleteElements();
	delete this->blockState;
	delete this->autoConstructor;
}

void StatementBlock::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->setParent(this);
		stmt->preAnalyze(actx);
	}
}

void StatementBlock::adjustDecalutConstructorCall(AnalyzeContext* actx) {
	ClassDeclare* clazzDec = getClassDeclare();
	ClassExtends* ext = clazzDec->getExtends();

	int maxLoop = this->statements.size();
	if(ext != nullptr){
		if(maxLoop == 0 || (maxLoop > 0 && !this->statements.get(0)->hasConstructor())){
			addConstructor(actx);
		}
	}

	for(int i = 1; i < maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);

		if(stmt->hasConstructor()){
			actx->addValidationError(ValidationError::CODE_CONSTRUCTOR_MUST_BE_FIRST_STMT, stmt
					, L"The super class constructor must be at the first of constructor.", {});
			break;
		}
	}
}

void StatementBlock::addConstructor(AnalyzeContext* actx) {
	this->autoConstructor = new ExpressionStatement();
	this->autoConstructor->setPosition(this);
	this->autoConstructor->setParent(this);

	FunctionCallExpression* call = new FunctionCallExpression();
	call->setPosition(this);

	VariableIdentifier* valId = new VariableIdentifier();
	UnicodeString* name = new UnicodeString(VariableIdentifier::__SUPER);
	valId->setName(name);

	call->setName(valId);

	this->autoConstructor->setExpression(call);

	this->autoConstructor->preAnalyze(actx);
}

void StatementBlock::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->autoConstructor != nullptr){
		this->autoConstructor->analyzeTypeRef(actx);
	}

	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->analyzeTypeRef(actx);
	}
}

void StatementBlock::analyze(AnalyzeContext* actx) {
	if(this->blockState == nullptr){
		analyzeBlockState(actx);
	}

	short parentKind = this->parent->getKind();
	if(parentKind == CodeElement::METHOD_DECLARE){
		analyzeMethodDeclareBlock(actx);
		return;
	}

	AnalyzeStackManager* stackMgr = actx->getAnalyzeStackManager();
	AnalyzeStackPopper popper(stackMgr, false);
	stackMgr->addBlockStack();

	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->analyze(actx);
	}

	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		if(stmt->hasCtrlStatement()){
			this->bctrl = true;
			break;
		}
	}
}

void StatementBlock::analyzeBlockState(AnalyzeContext* actx) {
	short parentKind = this->parent->getKind();
	if(parentKind == CodeElement::METHOD_DECLARE){
		this->blockState = new BlockState(BlockState::BLOCK_METHOD);
		return;
	}

	this->blockState = new BlockState(BlockState::BLOCK_NORMAL);
}

void StatementBlock::analyzeMethodDeclareBlock(AnalyzeContext* actx) {
	TypeResolver* typeResolver = actx->getTypeResolver();

	MethodDeclare* method = dynamic_cast<MethodDeclare*>(this->parent);

	AnalyzeStackManager* stackMgr = actx->getAnalyzeStackManager();
	AnalyzeStackPopper popper(stackMgr, true);
	stackMgr->addFunctionStack();

	AnalyzeStack* stack = stackMgr->top();

	if(!method->isStatic()){
		AnalyzedType* type = typeResolver->getClassType(method); __STP(type);
		AnalyzedStackReference* ref = new AnalyzedStackReference(&AnalyzedStackReference::THIS, type);
		stack->addVariableDeclare(ref);
	}

	ArgumentsListDeclare* arguments = method->getArguments();
	buildFunctionArguments2AnalyzedStack(arguments, stack);

	if(this->autoConstructor != nullptr){
		this->autoConstructor->analyze(actx);
	}

	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->analyze(actx);
	}
}

void StatementBlock::buildFunctionArguments2AnalyzedStack(ArgumentsListDeclare* arguments, AnalyzeStack* stack) const {
	const ArrayList<ArgumentDeclare>* list = arguments->getArguments();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		ArgumentDeclare* arg = list->get(i);
		const AnalyzedType* at = arg->getAnalyzedType();
		const UnicodeString* n = arg->getName();

		AnalyzedStackReference* ref = new AnalyzedStackReference(n, at);
		stack->addVariableDeclare(ref);
	}
}


void StatementBlock::addStatement(AbstractStatement* stmt) noexcept {
	this->statements.addElement(stmt);
}

void StatementBlock::setBlockState(BlockState* state) noexcept {
	this->blockState = state;
}

int StatementBlock::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		total += stmt->binarySize();
	}

	return total;
}

void StatementBlock::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::STMT_BLOCK);

	int maxLoop = this->statements.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->toBinary(out);
	}
}

void StatementBlock::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkIsStatement(element);

		AbstractStatement* stmt = dynamic_cast<AbstractStatement*>(element);
		this->statements.addElement(stmt);
	}
}

void StatementBlock::init(VirtualMachine* vm) {
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->init(vm);
	}
}

void StatementBlock::interpret(VirtualMachine* vm) {
	vm->newStack();
	StackPopper stackPopper(vm);

	// put this pointer on stack
	if(this->parent->getKind() == CodeElement::METHOD_DECLARE){
		interpretFunctionArguments(vm);
	}


	ExecControlManager* ctrl = vm->getCtrl();

	if(this->autoConstructor != nullptr){
		this->autoConstructor->interpret(vm);

		int stat = ctrl->checkStatementCtrl(this->blockState, this->autoConstructor);
		if(stat == AbstractCtrlInstruction::RET_BREAK || stat == AbstractCtrlInstruction::RET_CONTINUE || stat == AbstractCtrlInstruction::RET_THROW){
			return;
		}
	}

	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->interpret(vm);

		// control
		if(stmt->hasCtrlStatement()){
			int stat = ctrl->checkStatementCtrl(this->blockState, stmt);
			if(stat == AbstractCtrlInstruction::RET_BREAK || stat == AbstractCtrlInstruction::RET_CONTINUE || stat == AbstractCtrlInstruction::RET_THROW){
				break;
			}
		}
	}
}

bool StatementBlock::hasCtrlStatement() const noexcept {
	return this->bctrl;
}


bool StatementBlock::hasConstructor() const noexcept {
	bool ret = false;

	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);

		ret = ret || stmt->hasConstructor();
	}

	return ret;
}

void StatementBlock::interpretFunctionArguments(VirtualMachine* vm) {
	MethodDeclare* method = dynamic_cast<MethodDeclare*>(this->parent);
	FunctionArguments* args = vm->getFunctionArguments();
	VmStack* stack = vm->topStack();

	if(!method->isStatic()){
		VmClassInstance* _this = args->getThisPtr();
		ObjectReference* ref = ObjectReference::createObjectReference(stack, _this, vm);

		stack->addInnerReference(ref);
	}

	const ArrayList<IAbstractVmInstanceSubstance>* list = args->getArguments();
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		IAbstractVmInstanceSubstance* inst = list->get(i);


		if(inst != nullptr){
			stack->addInnerReference(inst->wrap(stack, vm));
		}
		else{
			ObjectReference* ref = ObjectReference::createObjectReference(stack, nullptr, vm);
			stack->addInnerReference(ref);
		}
	}
}

} /* namespace alinous */
