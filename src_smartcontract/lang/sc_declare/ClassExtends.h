/*
 * ClassExtends.h
 *
 *  Created on: 2019/06/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSEXTENDS_H_
#define SC_DECLARE_CLASSEXTENDS_H_

#include "engine/sc/CodeElement.h"

namespace alinous {

class ClassName;
class AnalyzeContext;
class AnalyzedType;
class UnicodeString;

class ClassExtends : public CodeElement {
public:
	ClassExtends();
	virtual ~ClassExtends();

	void preAnalyze(AnalyzeContext* actx);
	void analyzeTypeRef(AnalyzeContext* actx);

	void setClassName(ClassName* className) noexcept;
	void setClassName(const UnicodeString* className) noexcept;

	AnalyzedType* getAnalyzedType() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	ClassName* className;
	AnalyzedType* atype;

};

} /* namespace alinous */

#endif /* SC_DECLARE_CLASSEXTENDS_H_ */
