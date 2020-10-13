/*
 * SQLAdditiveExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_
#define SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_

#include "lang_sql/sql_expression/AbstractSQLBinaryExpression.h"
#include "base/RawArrayPrimitive.h"
#include <cstdint>

namespace alinous {

class SQLAdditiveExpression : public AbstractSQLBinaryExpression {
public:
	static const constexpr uint8_t ADD{1};
	static const constexpr uint8_t SUB{2};

	SQLAdditiveExpression();
	virtual ~SQLAdditiveExpression();

	void addOpe(uint8_t ope) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
	virtual void onSelectTarget(VirtualMachine* vm);
private:
	RawArrayPrimitive<uint8_t> operations;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_ */
