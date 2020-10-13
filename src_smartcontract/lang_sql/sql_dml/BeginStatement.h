/*
 * BeginStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_BEGINSTATEMENT_H_
#define SQL_DML_BEGINSTATEMENT_H_

#include "lang_sql/sql/AbstractSQLStatement.h"

namespace alinous {

class BeginStatement : public AbstractSQLStatement {
public:
	BeginStatement();
	virtual ~BeginStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* SQL_DML_BEGINSTATEMENT_H_ */
