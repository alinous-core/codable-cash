/*
 * SmartContract.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "engine/sc/SmartContract.h"
#include "engine/sc/CompilationUnit.h"

#include "engine/compiler/SmartContractParser.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/PackageSpace.h"
#include "engine/sc_analyze/AnalyzedClass.h"

#include "engine/sc_analyze_stack/AnalyzeStackPopper.h"
#include "engine/sc_analyze_stack/AnalyzeStackManager.h"

#include "base/UnicodeString.h"

#include "lang/sc_declare/ClassDeclare.h"
#include "lang/sc_declare/MethodDeclare.h"

#include "instance/VmClassInstance.h"
#include "instance_ref/ObjectReference.h"
#include "instance_ref/VmRootReference.h"

#include "instance_gc/GcManager.h"


#include "base_io_stream/FileInputStream.h"
#include "base_io/File.h"

#include "stack/StackPopper.h"
#include "stack/VmStack.h"

#include "engine/compiler/CompileError.h"
#include "engine/compiler/ParseErrorHandler.h"

#include "ext_arguments/AbstractFunctionExtArguments.h"

#include "reserved_classes/ReservedClassRegistory.h"

#include "base/Exception.h"

#include "instance_exception/ExceptionInterrupt.h"

#include "instance_ref_class_static/StaticClassReferenceHolder.h"


namespace alinous {

SmartContract::SmartContract() {
	this->actx = nullptr;
	this->mainPackage = nullptr;
	this->mainClass = nullptr;
	this->mainMethod = nullptr;
	this->rootReference = nullptr;
	this->initialized = false;
	this->reservedClassRegistory = new ReservedClassRegistory();
}

SmartContract::~SmartContract() {
	this->progs.deleteElements();
	delete this->actx;
	delete this->mainPackage;
	delete this->mainClass;
	delete this->mainMethod;
	delete this->rootReference;
	delete this->reservedClassRegistory;

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
	const ArrayList<AnalyzedClass>* list = this->reservedClassRegistory->getReservedClassesList();
	CompilationUnit* reservedUnit = this->reservedClassRegistory->getUnit();

	this->actx = new AnalyzeContext();
	this->actx->setVm(vm);
	this->actx->resigterReservedClasses();

	// pre analyze
	int maxLoop = this->progs.size();
	for(int i = 0; i != maxLoop; ++i){
		CompilationUnit* unit = this->progs.get(i);
		unit->preAnalyze(this->actx);
	}
	maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedClass* cls = list->get(i);
		ClassDeclare* dec = cls->getClassDeclare();

		dec->setParent(reservedUnit);
		dec->preAnalyze(actx);
	}

	if(this->actx->hasError()){
		return;
	}

	maxLoop = this->progs.size();
	for(int i = 0; i != maxLoop; ++i){
		CompilationUnit* unit = this->progs.get(i);
		unit->analyzeType(this->actx);
	}

	maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedClass* cls = list->get(i);
		ClassDeclare* dec = cls->getClassDeclare();

		dec->analyzeTypeRef(actx);
	}


	if(this->actx->hasError()){
		return;
	}

	// static meta data
	this->actx->analyzeStaticVariables();

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

		maxLoop = this->progs.size();
		for(int i = 0; i != maxLoop; ++i){
			CompilationUnit* unit = this->progs.get(i);
			unit->analyze(this->actx);
		}

		maxLoop = list->size();
		for(int i = 0; i != maxLoop; ++i){
			AnalyzedClass* cls = list->get(i);
			ClassDeclare* dec = cls->getClassDeclare();

			dec->analyze(actx);
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
	this->rootReference->resetOnGc();
	delete this->rootReference;
	this->rootReference = nullptr;
}
void SmartContract::releaseMainInstance(GcManager* gc) noexcept {
	this->rootReference->releaseMainInstance(gc);
}


VmClassInstance* SmartContract::createInstance(VirtualMachine* vm) {
	initialize(vm);

	PackageSpace* space = this->actx->getPackegeSpace(this->mainPackage);
	AnalyzedClass* clazz = space->getClass(this->mainClass);

	MethodDeclare* defConstructor = clazz->getDefaultConstructor();

	GcManager* gc = vm->getGc();
	vm->newStack();
	StackPopper popStack(vm);
	VmStack* stack = vm->topStack();

	VmClassInstance* inst = nullptr;

	try{
		inst = VmClassInstance::createObject(clazz, vm);
	}
	catch(ExceptionInterrupt* e){
		delete e;
		return nullptr;
	}


	this->rootReference->setMainInstance(inst);

	ObjectReference* instRef = ObjectReference::createObjectReference(stack, inst, vm);
	stack->addInnerReference(instRef);

	// exec constructor
	try{
		ArrayList<AbstractFunctionExtArguments> arguments;
		vm->interpret(defConstructor, inst, &arguments);
	}
	catch(Exception* e){
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

	StaticClassReferenceHolder* staticClassHolder = this->rootReference->getStaticClassReferenceHolder();
	staticClassHolder->init(vm, actx);

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

ReservedClassRegistory* SmartContract::getReservedClassRegistory() const noexcept {
	return this->reservedClassRegistory;
}

} /* namespace alinous */
