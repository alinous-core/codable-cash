/*
 * AnalyzeContext.cpp
 *
 *  Created on: 2019/05/22
 *      Author: iizuka
 */
#include "sc_analyze/AnalyzeContext.h"
#include "base/Iterator.h"
#include "base/UnicodeString.h"

#include "sc_analyze/PackageSpace.h"
namespace alinous {

AnalyzeContext::AnalyzeContext() {
	this->vm = nullptr;
	this->packageSpaces = new HashMap<UnicodeString, PackageSpace>();
}

AnalyzeContext::~AnalyzeContext() {
	this->vm = nullptr; // safe

	Iterator<UnicodeString>* it = this->packageSpaces->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* n = it->next();
		PackageSpace* space = this->packageSpaces->get(n);
		delete space;
	}
	delete it;

	delete this->packageSpaces;
}

void AnalyzeContext::setVm(VirtualMachine* vm) noexcept {
	this->vm = vm;
}

PackageSpace* AnalyzeContext::getPackegeSpace(const UnicodeString* spaceName) noexcept {
	PackageSpace* space = this->packageSpaces->get(spaceName);
	if(space == nullptr){
		space = new PackageSpace(spaceName);
		this->packageSpaces->put(spaceName, space);
	}

	return space;
}

} /* namespace alinous */
