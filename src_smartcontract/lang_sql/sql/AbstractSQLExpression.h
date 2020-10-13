/*
 * AbstractSQLExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_ABSTRACTSQLEXPRESSION_H_
#define SQL_ABSTRACTSQLEXPRESSION_H_

#include "lang_sql/sql/ISQLElement.h"
#include "engine/sc/CodeElement.h"

namespace alinous {

class AnalyzeContext;
class VirtualMachine;
class AnalyzedType;
class AbstractVmInstance;

class AbstractSQLExpression: public CodeElement, public ISQLElement {
public:
	explicit AbstractSQLExpression(int kind);
	virtual ~AbstractSQLExpression();

	virtual void preAnalyze(AnalyzeContext* actx) = 0;
	virtual void analyzeTypeRef(AnalyzeContext* actx) = 0;
	virtual void analyze(AnalyzeContext* actx) = 0;
	virtual AnalyzedType getType(AnalyzeContext* actx) = 0;

	virtual void init(VirtualMachine* vm) = 0;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm) = 0;
	virtual void onSelectTarget(VirtualMachine* vm) = 0;

	virtual bool isExecutable();
	void setExecutable(bool executable) noexcept;
private:
	bool executable;
};

} /* namespace alinous */

#endif /* SQL_ABSTRACTSQLEXPRESSION_H_ */
