/*
 * RelationalExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_RELATIONALEXPRESSION_H_
#define SC_EXPRESSION_RELATIONALEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"
#include <cstdint>

namespace alinous {

class RelationalExpression : public AbstractExpression {
public:
	static const constexpr uint8_t GT{1};
	static const constexpr uint8_t GT_EQ{2};
	static const constexpr uint8_t LT{3};
	static const constexpr uint8_t LT_EQ{4};

	RelationalExpression();
	virtual ~RelationalExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeType(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setLeft(AbstractExpression* exp) noexcept;
	void setRight(AbstractExpression* exp) noexcept;
	void setOp(uint8_t op) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType();
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
private:
	AbstractExpression* left;
	AbstractExpression* right;
	uint8_t op;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_RELATIONALEXPRESSION_H_ */
