/*
 * AbstractArithmeticBinaryExpresson.h
 *
 *  Created on: 2020/03/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICBINARYEXPRESSON_H_
#define SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICBINARYEXPRESSON_H_

#include "lang/sc_expression/AbstractBinaryExpression.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "base/RawArrayPrimitive.h"
#include <cstdint>


namespace alinous {

class AnalyzedType;
class AnalyzeContext;

class AbstractArithmeticBinaryExpresson: public AbstractBinaryExpression {
public:
	explicit AbstractArithmeticBinaryExpresson(int kind);
	virtual ~AbstractArithmeticBinaryExpresson();

	virtual AnalyzedType getType(AnalyzeContext* actx);
	void addOpe(uint8_t ope) noexcept;

	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
protected:
	RawArrayPrimitive<uint8_t> operations;

	// analyzed
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICBINARYEXPRESSON_H_ */
