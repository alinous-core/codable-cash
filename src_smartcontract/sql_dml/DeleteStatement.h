/*
 * DeleteStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_DELETESTATEMENT_H_
#define SQL_DML_DELETESTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {
class SQLFrom;
class SQLWhere;

class DeleteStatement : public AbstractSQLStatement {
public:
	DeleteStatement();
	virtual ~DeleteStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setFrom(SQLFrom* from) noexcept;
	void setWhere(SQLWhere* where) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	SQLFrom* from;
	SQLWhere* where;
};

} /* namespace alinous */

#endif /* SQL_DML_DELETESTATEMENT_H_ */
