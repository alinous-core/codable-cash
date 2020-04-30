/*
 * StaticClassMetadataHolder.cpp
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#include "instance_ref_class_static_meta/StaticClassMetadataHolder.h"
#include "instance_ref_class_static_meta/StaticClassMetadata.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"


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

} /* namespace alinous */
