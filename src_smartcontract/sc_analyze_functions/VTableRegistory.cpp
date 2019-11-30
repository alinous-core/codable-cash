/*
 * VTableRegistory.cpp
 *
 *  Created on: 2019/11/26
 *      Author: iizuka
 */

#include "sc_analyze_functions/VTableRegistory.h"
#include "sc_analyze_functions/VTableClassEntry.h"

#include "sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"

#include "base/Iterator.h"
#include "base/StackRelease.h"


namespace alinous {

VTableRegistory::VTableRegistory() {

}

VTableRegistory::~VTableRegistory() {
	Iterator<UnicodeString>* it = this->classEntries.keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* name = it->next();
		VTableClassEntry* entry = this->classEntries.get(name);

		delete entry;
	}
}

VTableClassEntry* VTableRegistory::getClassEntry(UnicodeString* fqn, AnalyzedClass* aclazz) noexcept {
	VTableClassEntry* entry = this->classEntries.get(fqn);
	if(entry == nullptr){
		entry = new VTableClassEntry(aclazz);
		this->classEntries.put(fqn , entry);
	}

	return entry;
}

} /* namespace alinous */
