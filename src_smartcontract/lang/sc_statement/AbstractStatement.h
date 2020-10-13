/*
 * AbstractStatement.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_ABSTRACTSTATEMENT_H_
#define SC_STATEMENT_ABSTRACTSTATEMENT_H_

#include "engine/sc/CodeElement.h"

namespace alinous {

class AnalyzeContext;
class VirtualMachine;

class AbstractStatement : public CodeElement {
public:
	explicit AbstractStatement(short kind);
	virtual ~AbstractStatement();

	virtual void preAnalyze(AnalyzeContext* actx) = 0;
	virtual void analyzeTypeRef(AnalyzeContext* actx) = 0;
	virtual void analyze(AnalyzeContext* actx) = 0;

	virtual void init(VirtualMachine* vm) = 0;
	virtual void interpret(VirtualMachine* vm) = 0;

	virtual bool isExecutable();
	virtual bool hasCtrlStatement() const noexcept = 0;

	virtual bool hasConstructor() const noexcept;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_ABSTRACTSTATEMENT_H_ */
