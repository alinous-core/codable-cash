/*
 * VTableMethodEntry.cpp
 *
 *  Created on: 2019/11/30
 *      Author: iizuka
 */

#include "sc_analyze_functions/VTableMethodEntry.h"

namespace alinous {

VTableMethodEntry::VTableMethodEntry(MethodDeclare* method, int type) {
	this->method = method;
	this->type = type;
}

VTableMethodEntry::~VTableMethodEntry() {
}

} /* namespace alinous */
