/*
 * SQLLikeExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLLIKEEXPRESSION_H_
#define SQL_EXPRESSION_SQLLIKEEXPRESSION_H_

#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {
class SQLLiteral;

class SQLLikeExpression : public AbstractSQLExpression {
public:
	SQLLikeExpression();
	virtual ~SQLLikeExpression();

	void setLeft(AbstractSQLExpression* left) noexcept;
	void setRight(SQLLiteral* right) noexcept;
	void setEscape(SQLLiteral* escape) noexcept;

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
	SQLLiteral* right;
	SQLLiteral* escape;

};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLLIKEEXPRESSION_H_ */
