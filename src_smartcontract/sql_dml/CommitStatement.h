/*
 * CommitStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_COMMITSTATEMENT_H_
#define SQL_DML_COMMITSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class CommitStatement : public AbstractSQLStatement {
public:
	CommitStatement();
	virtual ~CommitStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* SQL_DML_COMMITSTATEMENT_H_ */
