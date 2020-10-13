/*
 * SQLRelationalExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLRELATIONALEXPRESSION_H_
#define SQL_EXPRESSION_SQLRELATIONALEXPRESSION_H_

#include "lang_sql/sql/AbstractSQLExpression.h"
#include <cstdint>

namespace alinous {

class SQLRelationalExpression : public AbstractSQLExpression {
public:
	static const constexpr uint8_t GT{1};
	static const constexpr uint8_t GT_EQ{2};
	static const constexpr uint8_t LT{3};
	static const constexpr uint8_t LT_EQ{4};

	SQLRelationalExpression();
	virtual ~SQLRelationalExpression();

	void setLeft(AbstractSQLExpression* exp) noexcept;
	void setRight(AbstractSQLExpression* exp) noexcept;
	void setOp(uint8_t op) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
	virtual void onSelectTarget(VirtualMachine* vm);
private:
	AbstractSQLExpression* left;
	AbstractSQLExpression* right;
	uint8_t op;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLRELATIONALEXPRESSION_H_ */
