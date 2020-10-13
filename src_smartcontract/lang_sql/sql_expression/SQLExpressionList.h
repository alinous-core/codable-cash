/*
 * SQLExpressionList.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLEXPRESSIONLIST_H_
#define SQL_DML_PARTS_SQLEXPRESSIONLIST_H_

#include "lang_sql/sql/AbstractSQLExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class SQLExpressionList : public AbstractSQLExpression {
public:
	SQLExpressionList();
	virtual ~SQLExpressionList();

	void addExpression(AbstractSQLExpression* exp) noexcept;
	int numExpressions() const noexcept;
	AbstractSQLExpression* getExpression(int i) const noexcept;

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
	ArrayList<AbstractSQLExpression> list;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLEXPRESSIONLIST_H_ */
