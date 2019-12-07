/*
 * VTableClassEntry.h
 *
 *  Created on: 2019/11/26
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_
#define SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_

#include "base/HashMap.h"

namespace alinous {

class AnalyzedClass;
class AnalyzeContext;
class UnicodeString;
class VTableMethodEntry;
class MethodDeclare;

class VTableClassEntry {
public:
	VTableClassEntry(AnalyzedClass* aclass);
	virtual ~VTableClassEntry();

	void buildVtable(AnalyzeContext* actx);

private:
	void addMethodEntry(MethodDeclare* method);
	void addVirtualMethodImplEntry(MethodDeclare* method);

	MethodDeclare* getSuperClassMethod(MethodDeclare* method) noexcept;

private:
	AnalyzedClass* aclass;
	HashMap<UnicodeString, VTableMethodEntry> methods;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_ */
