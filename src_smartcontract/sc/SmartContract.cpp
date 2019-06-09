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

#include "base/UnicodeString.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/MethodDeclare.h"


namespace alinous {

SmartContract::SmartContract() {
	this->actx = nullptr;
	this->mainPackage = nullptr;
	this->mainClass = nullptr;
	this->mainMethod = nullptr;
}

SmartContract::~SmartContract() {
	this->progs.deleteElements();
	delete this->actx;
	delete this->mainPackage;
	delete this->mainClass;
	delete this->mainMethod;
}

void alinous::SmartContract::setMainMethod(const UnicodeString* mainPackage,
		const UnicodeString* mainClass, const UnicodeString* mainMethod) {
	this->mainPackage = new UnicodeString(*mainPackage);
	this->mainClass = new UnicodeString(*mainClass);
	this->mainMethod = new UnicodeString(*mainMethod);
}

void SmartContract::addCompilationUnit(InputStream* stream, int length) {
	SmartContractParser parser(stream, length);

	CompilationUnit* unit = parser.parse();

	this->progs.addElement(unit);
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
		unit->analyze(this->actx);
	}
}

void SmartContract::createInstance(VirtualMachine* vm) {
	PackageSpace* space = this->actx->getPackegeSpace(this->mainPackage);
	AnalyzedClass* clazz = space->getClass(this->mainClass);



	MethodDeclare* defConstructor = clazz->getDefaultConstructor();



}

} /* namespace alinous */
