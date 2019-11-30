/*
 * VTableClassEntry.cpp
 *
 *  Created on: 2019/11/26
 *      Author: iizuka
 */

#include "sc_analyze_functions/VTableClassEntry.h"

#include "sc_analyze/AnalyzedClass.h"

namespace alinous {

VTableClassEntry::VTableClassEntry(AnalyzedClass* aclass) {
	this->aclass = aclass;
}

VTableClassEntry::~VTableClassEntry() {
	this->aclass = nullptr;
}

} /* namespace alinous */
