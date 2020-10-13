/*
 * SQLWildCard.h
 *
 *  Created on: 2020/08/22
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLWILDCARD_H_
#define SQL_EXPRESSION_SQLWILDCARD_H_

#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {

class SQLWildCard : public AbstractSQLExpression {
public:
	SQLWildCard();
	virtual ~SQLWildCard();

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
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLWILDCARD_H_ */
