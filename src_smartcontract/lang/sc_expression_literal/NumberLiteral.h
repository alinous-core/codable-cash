/*
 * NumberLiteral.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_NUMBERLITERAL_H_
#define SC_EXPRESSION_NUMBERLITERAL_H_

#include "lang/sc_expression/AbstractExpression.h"
#include "base/UnicodeString.h"

#include "engine/sc_analyze/AnalyzedType.h"

namespace alinous {
class UnicodeString;
class PrimitiveReference;

class NumberLiteral : public AbstractExpression {
public:
	static const UnicodeString l;
	static const UnicodeString L;

	NumberLiteral();
	virtual ~NumberLiteral();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setValue(UnicodeString* str) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
private:
	UnicodeString* str;

	int64_t value;
	AnalyzedType atype;

	PrimitiveReference* referene;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_NUMBERLITERAL_H_ */
