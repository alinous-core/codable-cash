/*
 * StaticClassMetadata.cpp
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#include "instance_ref_class_static_meta/StaticClassMetadata.h"
#include "instance_ref_class_static_meta/StaticVariableMetadata.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_declare/MemberVariableDeclare.h"

#include "base/ArrayList.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"


namespace alinous {

StaticClassMetadata::StaticClassMetadata(AnalyzedClass* clazz) {
	this->clazz = clazz;
	this->map = new HashMap<UnicodeString, StaticVariableMetadata>();
}

StaticClassMetadata::~StaticClassMetadata() {
	this->clazz = nullptr;

	Iterator<UnicodeString>* it = this->map->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		StaticVariableMetadata* meta = this->map->get(key);

		delete meta;
	}

	delete this->map;
}

void StaticClassMetadata::init() noexcept {
	ClassDeclare* dec = this->clazz->getClassDeclare();
	ArrayList<MemberVariableDeclare>* list = dec->getMemberVariables();

	int indexCount = 0;
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		MemberVariableDeclare* val = list->get(i);

		if(val->isStatic()){
			const UnicodeString* name = val->getName();
			StaticVariableMetadata* valmeta = new StaticVariableMetadata(indexCount, val);

			this->map->put(name, valmeta);
			indexCount++;
		}
	}
}

StaticVariableMetadata* StaticClassMetadata::findStaticVariableMetadata(const UnicodeString* name) const noexcept {
	StaticVariableMetadata* meta = this->map->get(name);

	// FIXME supre class

	return meta;
}


} /* namespace alinous */
