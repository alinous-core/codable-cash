/*
 * StaticClassMetadataHolder.cpp
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#include "instance/instance_ref_class_static_meta/StaticClassMetadataHolder.h"
#include "instance/instance_ref_class_static_meta/StaticClassMetadata.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "engine/sc_analyze/AnalyzedClass.h"
#include "lang/sc_declare/ClassDeclare.h"


namespace alinous {

StaticClassMetadataHolder::StaticClassMetadataHolder() {
	this->classMap = new HashMap<UnicodeString, StaticClassMetadata>();
}

StaticClassMetadataHolder::~StaticClassMetadataHolder() {
	Iterator<UnicodeString>* it = this->classMap->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		StaticClassMetadata* meta = this->classMap->get(key);

		delete meta;
	}

	delete this->classMap;
}

void StaticClassMetadataHolder::addClass(AnalyzedClass* clazz) noexcept {
	StaticClassMetadata* classMeta = newStaticClassMetadata(clazz);
	classMeta->init();
}

StaticVariableMetadata* StaticClassMetadataHolder::findVariableMetadata(const UnicodeString* classFqn, const UnicodeString* name) const noexcept {
	StaticClassMetadata* classMeta = this->classMap->get(classFqn);
	StaticVariableMetadata* valMeta = nullptr;

	if(classMeta != nullptr){
		valMeta = classMeta->findStaticVariableMetadata(name);
	}

	return valMeta;
}

void StaticClassMetadataHolder::analyzeInheritance() noexcept {
	Iterator<UnicodeString>* it = this->classMap->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		StaticClassMetadata* meta = this->classMap->get(key);

		meta->initInheritance(this);
	}
}

StaticClassMetadata* StaticClassMetadataHolder::getClassMetadata(const UnicodeString* fqn) const noexcept {
	return this->classMap->get(fqn);
}

StaticClassMetadata* StaticClassMetadataHolder::newStaticClassMetadata(AnalyzedClass* clazz) noexcept {
	const UnicodeString* fqn = clazz->getFullQualifiedName();
	StaticClassMetadata* meta = new StaticClassMetadata(clazz);

	this->classMap->put(fqn, meta);

	return meta;
}

} /* namespace alinous */
