/*
 * StaticClassMetadata.cpp
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#include "instance/instance_ref_class_static_meta/StaticClassMetadata.h"
#include "instance/instance_ref_class_static_meta/StaticVariableMetadata.h"
#include "instance/instance_ref_class_static_meta/StaticClassMetadataHolder.h"

#include "lang/sc_declare/ClassDeclare.h"
#include "lang/sc_declare/MemberVariableDeclare.h"

#include "engine/sc_analyze/AnalyzedClass.h"

#include "base/ArrayList.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"


namespace alinous {

StaticClassMetadata::StaticClassMetadata(AnalyzedClass* clazz) {
	this->clazz = clazz;
	this->map = new HashMap<UnicodeString, StaticVariableMetadata>();
	this->extClass = nullptr;
	this->classEntry = nullptr;
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
	this->extClass = nullptr;
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
			StaticVariableMetadata* valmeta = new StaticVariableMetadata(indexCount, val, this);

			this->map->put(name, valmeta);
			indexCount++;
		}
	}
}

void StaticClassMetadata::initInheritance(StaticClassMetadataHolder* holder) noexcept {
	AnalyzedClass* extClass = this->clazz->getExtends();
	if(extClass !=  nullptr){
		const UnicodeString* fqn = extClass->getFullQualifiedName();
		this->extClass = holder->getClassMetadata(fqn);
	}

	const ArrayList<AnalyzedClass>* list = this->clazz->getImplements();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedClass* cls = list->get(i);
		const UnicodeString* fqn = cls->getFullQualifiedName();

		StaticClassMetadata* meta = holder->getClassMetadata(fqn);
		this->implements.addElement(meta);
	}
}


StaticVariableMetadata* StaticClassMetadata::findStaticVariableMetadata(const UnicodeString* name) const noexcept {
	StaticVariableMetadata* meta = this->map->get(name);

	if(meta == nullptr && this->extClass != nullptr){
		meta = this->extClass->findStaticVariableMetadata(name);
	}

	if(meta == nullptr){
		int maxLoop = this->implements.size();
		for(int i = 0; i != maxLoop && meta == nullptr; ++i){
			StaticClassMetadata* cls = this->implements.get(i);

			meta = cls->findStaticVariableMetadata(name);
		}
	}

	return meta;
}

void StaticClassMetadata::setClassEntry(StaticClassEntry* classEntry) noexcept {
	this->classEntry = classEntry;
}

StaticClassEntry* StaticClassMetadata::getStaticClassEntry() const noexcept {
	return this->classEntry;
}

} /* namespace alinous */
