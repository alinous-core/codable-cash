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
#include "sc_declare/ArgumentsListDeclare.h"

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
		const UnicodeString* sigStr = method->getCallSignature();

		MethodDeclare* superMethod = getSuperClassMethod(method);
		if(superMethod == nullptr){
			continue;
		}

		// FIXME error check
	}
}

MethodDeclare* VTableClassEntry::getSuperClassMethod(MethodDeclare* method) noexcept {
	MethodDeclare* superMethod = nullptr;

	const UnicodeString* name = method->getName();
	ArgumentsListDeclare* argList = method->getArguments();
	ArrayList<AnalyzedType>* typeList = argList->getArgumentsAnalyzedType();

	AnalyzedClass* superClass = this->aclass->getExtends();
	while(superClass != nullptr){
		superMethod = superClass->findMethod(name, typeList);

		if(superMethod != nullptr){
			return superMethod;
		}

		superClass = superClass->getExtends();
	}

	return nullptr;
}

} /* namespace alinous */
