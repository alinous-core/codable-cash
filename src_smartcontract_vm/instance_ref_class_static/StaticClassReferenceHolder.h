/*
 * StaticClassReferenceHolder.h
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_STATICCLASSREFERENCEHOLDER_H_
#define INSTANCE_REF_CLASS_STATIC_STATICCLASSREFERENCEHOLDER_H_

#include "base/HashMap.h"


namespace alinous {

class AnalyzeContext;
class UnicodeString;
class StaticClassEntry;
class VirtualMachine;
class VmRootReference;
class PackageSpace;

class StaticClassReferenceHolder {
public:
	StaticClassReferenceHolder();
	virtual ~StaticClassReferenceHolder();

	void init(VirtualMachine* vm, AnalyzeContext* actx);
	void removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept;

private:
	void initPackageSpace(VirtualMachine* vm, PackageSpace* space);
private:
	HashMap<UnicodeString, StaticClassEntry>* classMap;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_STATICCLASSREFERENCEHOLDER_H_ */
