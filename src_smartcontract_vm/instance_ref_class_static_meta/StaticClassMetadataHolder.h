/*
 * StaticClassMetadataHolder.h
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATAHOLDER_H_
#define INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATAHOLDER_H_

#include "base/HashMap.h"


namespace alinous {

class UnicodeString;
class StaticClassMetadata;

class StaticClassMetadataHolder {
public:
	StaticClassMetadataHolder();
	virtual ~StaticClassMetadataHolder();

private:
	HashMap<UnicodeString, StaticClassMetadata>* classMap;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATAHOLDER_H_ */
