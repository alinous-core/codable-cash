/*
 * StaticClassMetadata.h
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATA_H_
#define INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATA_H_

#include "base/HashMap.h"
#include "base/ArrayList.h"


namespace alinous {

class AnalyzedClass;
class StaticVariableMetadata;
class StaticClassMetadata;
class StaticClassMetadataHolder;
class UnicodeString;
class StaticClassEntry;

class StaticClassMetadata {
public:
	explicit StaticClassMetadata(AnalyzedClass* clazz);
	virtual ~StaticClassMetadata();

	void init() noexcept;
	void initInheritance(StaticClassMetadataHolder* holder) noexcept;
	StaticVariableMetadata* findStaticVariableMetadata(const UnicodeString* name) const noexcept;

	void setClassEntry(StaticClassEntry* classEntry) noexcept;
	StaticClassEntry* getStaticClassEntry() const noexcept;
private:
	AnalyzedClass* clazz;
	HashMap<UnicodeString, StaticVariableMetadata>* map;

	StaticClassMetadata* extClass;
	ArrayList<StaticClassMetadata> implements;

	StaticClassEntry* classEntry;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATA_H_ */
