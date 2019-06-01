/*
 * CreateTableStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DDL_CREATETABLESTATEMENT_H_
#define SQL_DDL_CREATETABLESTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class CreateTableStatement : public AbstractSQLStatement {
public:
	CreateTableStatement();
	virtual ~CreateTableStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SQL_DDL_CREATETABLESTATEMENT_H_ */
