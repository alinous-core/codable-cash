/*
 * AlterTableStatement.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTERTABLESTATEMENT_H_
#define SQL_DDL_ALTERTABLESTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class AlterTableStatement : public AbstractSQLStatement {
public:
	AlterTableStatement();
	virtual ~AlterTableStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);

};

} /* namespace alinous */

#endif /* SQL_DDL_ALTERTABLESTATEMENT_H_ */
