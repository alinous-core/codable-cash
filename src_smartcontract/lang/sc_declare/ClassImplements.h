/*
 * ClassImplements.h
 *
 *  Created on: 2019/06/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSIMPLEMENTS_H_
#define SC_DECLARE_CLASSIMPLEMENTS_H_

#include "engine/sc/CodeElement.h"
#include "base/ArrayList.h"

namespace alinous {

class ClassName;
class AnalyzeContext;
class AnalyzedType;

class ClassImplements : public CodeElement {
public:
	ClassImplements();
	virtual ~ClassImplements();

	void preAnalyze(AnalyzeContext* actx);
	void analyzeTypeRef(AnalyzeContext* actx);

	void addClassName(ClassName* name) noexcept;
	const ArrayList<AnalyzedType>* getAnalyzedTypes() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	ArrayList<ClassName> list;
	ArrayList<AnalyzedType> typelist;
};

} /* namespace alinous */

#endif /* SC_DECLARE_CLASSIMPLEMENTS_H_ */
