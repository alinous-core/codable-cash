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

namespace alinous {

SmartContract::SmartContract() {
	this->actx = nullptr;

}

SmartContract::~SmartContract() {
	this->progs.deleteElements();
	delete this->actx;
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

	for(int i = 0; i != maxLoop; ++i){
		CompilationUnit* unit = this->progs.get(i);
		unit->analyze(this->actx);
	}
}

} /* namespace alinous */

