/*
 * StatementBlock.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "sc_statement/StatementBlock.h"

#include "sc_declare/MethodDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_declare/ArgumentDeclare.h"

#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze_stack/AnalyzeStackPopper.h"
#include "sc_analyze_stack/AnalyzedStackReference.h"
#include "sc_analyze_stack/AnalyzeStack.h"

#include "base/StackRelease.h"

#include "stack/StackPopper.h"
#include "stack/VmStack.h"

#include "instance_ref/ObjectReference.h"

#include "variable_access/FunctionArguments.h"

#include "vm_ctrl/BlockState.h"
#include "vm_ctrl/ExecControlManager.h"

namespace alinous {

StatementBlock::StatementBlock() : AbstractStatement(CodeElement::STMT_BLOCK) {
	this->blockState = nullptr;
}

StatementBlock::~StatementBlock() {
	this->statements.deleteElements();
	delete this->blockState;
}

void StatementBlock::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->setParent(this);
		stmt->preAnalyze(actx);
	}
}

void StatementBlock::analyzeTypeRef(AnalyzeContext* actx) {
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

	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->interpret(vm);

		// control
		if(ctrl->checkStatementCtrl(this->blockState, stmt)){
			break;
		}
	}
}

void StatementBlock::interpretFunctionArguments(VirtualMachine* vm) {
	MethodDeclare* method = dynamic_cast<MethodDeclare*>(this->parent);
	FunctionArguments* args = vm->getFunctionArguments();
	VmStack* stack = vm->topStack();

	if(!method->isStatic()){
		VmClassInstance* _this = args->getThisPtr();
		ObjectReference* ref = ObjectReference::createObjectReference(stack, _this, vm, true);

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
			ObjectReference* ref = ObjectReference::createObjectReference(stack, nullptr, vm, true);
			stack->addInnerReference(ref);
		}
	}
}

} /* namespace alinous */
