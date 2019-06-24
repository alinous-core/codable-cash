/*
 * TypeResolver.cpp
 *
 *  Created on: 2019/06/23
 *      Author: iizuka
 */

#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/PackageSpace.h"
#include "sc_analyze/AnalyzedType.h"

#include "sc/CodeElement.h"
#include "sc/CompilationUnit.h"

#include "sc_declare/ImportsDeclare.h"
#include "sc_declare/ImportDeclare.h"

#include "base/StackRelease.h"
#include "base/ArrayList.h"

namespace alinous {

UnicodeString TypeResolver::DOT(L".");

TypeResolver::TypeResolver(AnalyzeContext* ctx) : ctx(ctx) {

}

TypeResolver::~TypeResolver() {

}



AnalyzedType* alinous::TypeResolver::findClassType(CodeElement* element, const UnicodeString* name) const {
	if(!isFqn(name)){
		CompilationUnit* unit = element->getCompilationUnit();

		// find import section
		ImportsDeclare* imports = unit->getImportDeclare();
		AnalyzedType* atype = findFromImports(name, imports);
		if(atype != nullptr){
			return atype;
		}

		// find same package
		const UnicodeString* packageName = unit->getPackageName();
		return findClassType(packageName, name);
	}

	UnicodeString* pkg = getPackageName(name); __STP(pkg);
	UnicodeString* clazz = getClassName(name); __STP(clazz);

	return findClassType(pkg, clazz);
}

AnalyzedType* TypeResolver::findFromImports(const UnicodeString* name, ImportsDeclare* imports) const {
	const ArrayList<ImportDeclare>* list = imports->getImports();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		ImportDeclare* imp = list->get(i);

		if(imp->hasClassName(name)){
			UnicodeString* pkgName = imp->getPackageName(); __STP(pkgName);
			return findClassType(pkgName, name);
		}
	}

	return nullptr;
}

AnalyzedType* TypeResolver::findClassType(const UnicodeString* packageName, const UnicodeString* name) const {
	PackageSpace* space = this->ctx->getPackegeSpace(packageName);
	if(space == nullptr){
		return nullptr; // error
	}

	AnalyzedClass* clazz = space->getClass(name);

	return new AnalyzedType(clazz);
}

bool alinous::TypeResolver::isFqn(const UnicodeString* name) noexcept {
	return 0 <= name->indexOf(L'.');
}

UnicodeString* TypeResolver::getPackageName(const UnicodeString* name) noexcept {
	int index = name->lastIndexOf(&DOT);
	if(index < 0){
		return nullptr;
	}

	return name->substring(0, index);
}

UnicodeString* TypeResolver::getClassName(const UnicodeString* name) noexcept {
	int index = name->lastIndexOf(&DOT);
	if(index < 0){
		return nullptr;
	}

	return name->substring(index + 1);
}

} /* namespace alinous */
