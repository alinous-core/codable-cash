/*
 * MemberFunctionCallAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/MemberFunctionCallAccess.h"

namespace alinous {

MemberFunctionCallAccess::MemberFunctionCallAccess() {
	// TODO Auto-generated constructor stub

}

MemberFunctionCallAccess::~MemberFunctionCallAccess() {
	// TODO Auto-generated destructor stub
}

void MemberFunctionCallAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	// FIXME analyze
}

AbstractVmInstance* MemberFunctionCallAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	return nullptr; // FIXME interpret
}

} /* namespace alinous */
