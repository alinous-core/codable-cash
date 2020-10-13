/*
 * SQLIsNullExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLISNULLEXPRESSION_H_
#define SQL_EXPRESSION_SQLISNULLEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLIsNullExpression : public AbstractSQLExpression {
public:
	SQLIsNullExpression();
	virtual ~SQLIsNullExpression();

	void setExpression(AbstractSQLExpression* exp) noexcept;
	void setNotNull(bool notnull) noexcept;

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
	AbstractSQLExpression* exp;
	bool notnull;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLISNULLEXPRESSION_H_ */
