/*
 * MethodNameCollection.h
 *
 *  Created on: 2019/12/12
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_METHODNAMECOLLECTION_H_
#define SC_ANALYZE_FUNCTIONS_METHODNAMECOLLECTION_H_

#include "base/ArrayList.h"

namespace alinous {

class VTableMethodEntry;

class MethodNameCollection {
public:
	MethodNameCollection();
	virtual ~MethodNameCollection();

	void addMethodEntry(VTableMethodEntry* entry) noexcept;
	const ArrayList<VTableMethodEntry>* getList() const noexcept;
private:
	ArrayList<VTableMethodEntry> list;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_METHODNAMECOLLECTION_H_ */
