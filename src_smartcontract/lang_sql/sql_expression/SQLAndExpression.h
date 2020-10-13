/*
 * SQLAndExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLANDEXPRESSION_H_
#define SQL_EXPRESSION_SQLANDEXPRESSION_H_

#include "lang_sql/sql_expression/AbstractSQLBinaryExpression.h"

namespace alinous {

class SQLAndExpression : public AbstractSQLBinaryExpression {
public:
	SQLAndExpression();
	virtual ~SQLAndExpression();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
	virtual void onSelectTarget(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLANDEXPRESSION_H_ */
