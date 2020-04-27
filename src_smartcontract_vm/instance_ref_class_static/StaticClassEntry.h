/*
 * StaticClassEntry.h
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_STATICCLASSENTRY_H_
#define INSTANCE_REF_CLASS_STATIC_STATICCLASSENTRY_H_

namespace alinous {

class AnalyzedClass;

class StaticClassEntry {
public:
	StaticClassEntry(AnalyzedClass* aclazz);
	virtual ~StaticClassEntry();

private:
	AnalyzedClass* aclazz;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_STATICCLASSENTRY_H_ */
