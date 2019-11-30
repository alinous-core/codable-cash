/*
 * VTableClassEntry.cpp
 *
 *  Created on: 2019/11/26
 *      Author: iizuka
 */

#include "sc_analyze_functions/VTableClassEntry.h"

#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze_functions/VTableMethodEntry.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/MethodDeclare.h"

#include "base/UnicodeString.h"

namespace alinous {

VTableClassEntry::VTableClassEntry(AnalyzedClass* aclass) {
	this->aclass = aclass;
}

VTableClassEntry::~VTableClassEntry() {
	this->aclass = nullptr;
}

void VTableClassEntry::buildVtable(AnalyzeContext* actx) {
	ClassDeclare* clazz = this->aclass->getClassDeclare();
	ArrayList<MethodDeclare>* list = clazz->getMethods();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MethodDeclare* method = list->get(i);


	}

}

} /* namespace alinous */
