/*
 * BooleanLiteral.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_BOOLEANLITERAL_H_
#define SC_EXPRESSION_BOOLEANLITERAL_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {

class BooleanLiteral : public AbstractExpression {
public:
	BooleanLiteral();
	virtual ~BooleanLiteral();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setValue(bool v) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType();
private:
	bool value;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_BOOLEANLITERAL_H_ */
