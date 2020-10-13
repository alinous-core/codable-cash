/*
 * AbstractAlterDdlCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_
#define SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_

#include "engine/sc/CodeElement.h"

namespace codablecash {
class AbstractAlterCommandLog;
}
using namespace codablecash;

namespace alinous {

class DdlColumnDescriptor;
class TableIdentifier;
class AnalyzeContext;
class VirtualMachine;

class AbstractAlterDdlCommand : public CodeElement {
public:
	explicit AbstractAlterDdlCommand(short kind);
	virtual ~AbstractAlterDdlCommand();

	virtual AbstractAlterCommandLog* getCommandLog() = 0;


	virtual void preAnalyze(AnalyzeContext* actx) = 0;
	virtual void analyzeTypeRef(AnalyzeContext* actx) = 0;
	virtual void analyze(AnalyzeContext* actx) = 0;
	virtual void interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) = 0;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_ */
