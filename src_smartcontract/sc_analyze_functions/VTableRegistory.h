/*
 * VTableRegistory.h
 *
 *  Created on: 2019/11/26
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_VTABLEREGISTORY_H_
#define SC_ANALYZE_FUNCTIONS_VTABLEREGISTORY_H_
#include "base/HashMap.h"

namespace alinous {

class VTableClassEntry;
class UnicodeString;
class AnalyzedClass;

class VTableRegistory {
public:
	VTableRegistory();
	virtual ~VTableRegistory();

	VTableClassEntry* getClassEntry(const UnicodeString* fqn, AnalyzedClass* aclazz) noexcept;

private:
	HashMap<UnicodeString, VTableClassEntry> classEntries;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_VTABLEREGISTORY_H_ */
