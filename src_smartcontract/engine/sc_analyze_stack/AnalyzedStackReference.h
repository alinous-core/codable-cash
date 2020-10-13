/*
 * AnalyzedStackReference.h
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZEDSTACKREFERENCE_H_
#define SC_ANALYZE_ANALYZEDSTACKREFERENCE_H_

namespace alinous {
class UnicodeString;
class AnalyzedType;

class AnalyzedStackReference {
public:
	static const UnicodeString THIS;

	AnalyzedStackReference(const UnicodeString* name, const AnalyzedType* type);
	virtual ~AnalyzedStackReference();

	const UnicodeString* getName() const noexcept;
	const AnalyzedType* getType() const noexcept;
private:
	UnicodeString* name;
	AnalyzedType* type;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZEDSTACKREFERENCE_H_ */
