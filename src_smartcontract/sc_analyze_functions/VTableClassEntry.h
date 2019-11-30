/*
 * VTableClassEntry.h
 *
 *  Created on: 2019/11/26
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_
#define SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_

namespace alinous {

class AnalyzedClass;

class VTableClassEntry {
public:
	VTableClassEntry(AnalyzedClass* aclass);
	virtual ~VTableClassEntry();

private:
	AnalyzedClass* aclass;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_VTABLECLASSENTRY_H_ */
