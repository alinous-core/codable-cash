/*
 * SmartContract.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "sc/SmartContract.h"
#include "sc/CompilationUnit.h"

#include "compiler/SmartContractParser.h"


namespace alinous {

SmartContract::SmartContract() {

}

SmartContract::~SmartContract() {
	this->progs.deleteElements();
}

void SmartContract::addCompilationUnit(InputStream* stream, int length) {
	SmartContractParser parser(stream, length);

	CompilationUnit* unit = parser.parse();

	this->progs.addElement(unit);
}

} /* namespace alinous */

