/*
 * SQLWhere.h
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLWHERE_H_
#define SQL_DML_PARTS_SQLWHERE_H_

#include "lang_sql/sql/AbstractSQLPart.h"

namespace alinous {

class AnalyzeContext;
class AbstractSQLExpression;
class AbstractVmInstance;
class VirtualMachine;

class SQLWhere : public AbstractSQLPart {
public:
	SQLWhere();
	virtual ~SQLWhere();

	void setExpression(AbstractSQLExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void preAnalyze(AnalyzeContext* actx);
	void analyzeTypeRef(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);

	void init(VirtualMachine* vm);
	AbstractVmInstance* interpret(VirtualMachine* vm);

	AbstractSQLExpression* getExp() const {
		return exp;
	}

private:
	AbstractSQLExpression* exp;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLWHERE_H_ */
