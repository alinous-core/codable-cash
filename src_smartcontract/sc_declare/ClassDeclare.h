/*
 * ClassDeclare.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSDECLARE_H_
#define SC_DECLARE_CLASSDECLARE_H_

#include "sc/CodeElement.h"

#include "base/ArrayList.h"

namespace alinous {

class ClassDeclareBlock;
class UnicodeString;
class AnalyzeContext;

class ClassDeclare : public CodeElement {
public:
	ClassDeclare();
	virtual ~ClassDeclare();

	void preAnalyze(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);

	void setBlock(ClassDeclareBlock* block) noexcept;
	void setName(UnicodeString* name) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	ClassDeclareBlock* block;
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* SC_DECLARE_CLASSDECLARE_H_ */
