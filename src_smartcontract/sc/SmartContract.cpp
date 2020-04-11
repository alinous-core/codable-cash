/*
 * SmartContract.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "sc/SmartContract.h"
#include "sc/CompilationUnit.h"

#include "compiler/SmartContractParser.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/PackageSpace.h"
#include "sc_analyze/AnalyzedClass.h"

#include "sc_analyze_stack/AnalyzeStackPopper.h"
#include "sc_analyze_stack/AnalyzeStackManager.h"

#include "base/UnicodeString.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/MethodDeclare.h"

#include "instance/VmClassInstance.h"
#include "instance_ref/ObjectReference.h"
#include "instance_ref/VmRootReference.h"

#include "instance_gc/GcManager.h"

#include "instance_exception/AbstractProgramException.h"

#include "base_io_stream/FileInputStream.h"
#include "base_io/File.h"

#include "stack/StackPopper.h"
#include "stack/VmStack.h"

#include "compiler/CompileError.h"
#include "compiler/ParseErrorHandler.h"

#include "ext_arguments/AbstractFunctionExtArguments.h"

namespace alinous {

SmartContract::SmartContract() {
	this->actx = nullptr;
	this->mainPackage = nullptr;
	this->mainClass = nullptr;
	this->mainMethod = nullptr;
	this->rootReference = nullptr;
	this->initialized = false;
}

SmartContract::~SmartContract() {
	this->progs.deleteElements();
	delete this->actx;
	delete this->mainPackage;
	delete this->mainClass;
	delete this->mainMethod;
	delete this->rootReference;

	this->compileErrorList.deleteElements();
}

void alinous::SmartContract::setMainMethod(const UnicodeString* mainPackage,
		const UnicodeString* mainClass, const UnicodeString* mainMethod) {
	if(mainPackage != nullptr){
		this->mainPackage = new UnicodeString(*mainPackage);
	}

	this->mainClass = new UnicodeString(*mainClass);
	this->mainMethod = new UnicodeString(*mainMethod);
}

void SmartContract::addCompilationUnit(InputStream* stream, int length, const File* base, File* source) {
	SmartContractParser parser(stream, length);

	CompilationUnit* unit = parser.parse();

	const ArrayList<CompileError>& errorList = parser.getParserErrorHandler()->getList();
	int maxLoop = errorList.size();
	for(int i = 0; i != maxLoop; ++i){
		CompileError* error = errorList.get(i);

		CompileError* newError = new CompileError(*error);
		this->compileErrorList.addElement(newError);
	}

	this->progs.addElement(unit);
}

void SmartContract::addCompilationUnit(File* file, const File* base) {
	FileInputStream stream(file);

	int length = file->length();
	addCompilationUnit(&stream, length, base, file);
}

void SmartContract::analyze(VirtualMachine* vm) {
	this->actx = new AnalyzeContext();
	this->actx->setVm(vm);

	int maxLoop = this->progs.size();
	for(int i = 0; i != maxLoop; ++i){
		CompilationUnit* unit = this->progs.get(i);
		unit->preAnalyze(this->actx);
	}

	if(this->actx->hasError()){
		return;
	}

	for(int i = 0; i != maxLoop; ++i){
		CompilationUnit* unit = this->progs.get(i);
		unit->analyzeType(this->actx);
	}

	if(this->actx->hasError()){
		return;
	}

	// inheritance
	this->actx->analyzeClassInheritance();

	if(this->actx->hasError()){
		return;
	}

	{
		// make top stack
		AnalyzeStackManager* stackMgr = actx->getAnalyzeStackManager();
		AnalyzeStackPopper popper(stackMgr, true);
		stackMgr->addFunctionStack();

		for(int i = 0; i != maxLoop; ++i){
			CompilationUnit* unit = this->progs.get(i);
			unit->analyze(this->actx);
		}
	}

}

bool SmartContract::hasError() noexcept {
	return this->actx->hasError();
}

VmRootReference* SmartContract::getRootReference() const noexcept {
	return this->rootReference;
}

void SmartContract::clearRootReference(VirtualMachine* vm) noexcept {
	delete this->rootReference;
	this->rootReference = nullptr;
}

VmClassInstance* SmartContract::createInstance(VirtualMachine* vm) {
	initialize(vm);

	PackageSpace* space = this->actx->getPackegeSpace(this->mainPackage);
	AnalyzedClass* clazz = space->getClass(this->mainClass);

	MethodDeclare* defConstructor = clazz->getDefaultConstructor();

	vm->newStack();
	StackPopper popStack(vm);
	VmStack* stack = vm->topStack();

	VmClassInstance* inst = VmClassInstance::createObject(clazz, vm);

	GcManager* gc = vm->getGc();

	this->rootReference->setMainInstance(inst);

	ObjectReference* instRef = ObjectReference::createObjectReference(stack, inst, vm, true);
	stack->addInnerReference(instRef);

	// exec constructor
	try{
		ArrayList<AbstractFunctionExtArguments> arguments;
		vm->interpret(defConstructor, inst, &arguments);
	}
	catch(AbstractProgramException* e){
		throw e;
	}

	return inst;
}

void SmartContract::initialize(VirtualMachine* vm) {
	if(this->initialized){
		return;
	}

	this->rootReference = new(vm) VmRootReference(vm);
	vm->setVmRootReference(this->rootReference);

	int maxLoop = this->progs.size();
	for(int i = 0; i != maxLoop; ++i){
		CompilationUnit* unit = this->progs.get(i);
		unit->init(vm);
	}

	this->initialized = true;
}

AnalyzeContext* SmartContract::getAnalyzeContext() const noexcept {
	return this->actx;
}

const ArrayList<CompileError>* SmartContract::getCompileErrors() const noexcept {
	return &this->compileErrorList;
}

CompilationUnit* SmartContract::getCompilationUnit(int pos) {
	return this->progs.get(pos);
}


} /* namespace alinous */
