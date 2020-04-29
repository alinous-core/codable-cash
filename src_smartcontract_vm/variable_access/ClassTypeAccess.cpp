/*
 * ClassTypeAccess.cpp
 *
 *  Created on: 2020/04/28
 *      Author: iizuka
 */

#include "variable_access/ClassTypeAccess.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "vm/VirtualMachine.h"

namespace alinous {

ClassTypeAccess::ClassTypeAccess()
		: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_CLASS_TYPE){

}

ClassTypeAccess::~ClassTypeAccess() {

}

void ClassTypeAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
}

AnalyzedType ClassTypeAccess::getAnalyzedType() const noexcept {
}

AbstractVmInstance* ClassTypeAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
}

CodeElement* ClassTypeAccess::getCodeElement() const noexcept {
}

} /* namespace alinous */
