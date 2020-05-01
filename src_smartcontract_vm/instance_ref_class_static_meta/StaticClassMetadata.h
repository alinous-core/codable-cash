/*
 * StaticClassMetadata.h
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATA_H_
#define INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATA_H_

namespace alinous {

class AnalyzedClass;
class StaticVariableMetadata;

class StaticClassMetadata {
public:
	explicit StaticClassMetadata(AnalyzedClass* clazz);
	virtual ~StaticClassMetadata();

	void init() noexcept;
private:
	AnalyzedClass* clazz;


};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_META_STATICCLASSMETADATA_H_ */
