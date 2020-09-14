/*
 * AbstractAlterDdlCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_
#define SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_

#include "sc/CodeElement.h"

namespace codablecash {
class AbstractDdlLog;
}
using namespace codablecash;

namespace alinous {

class DdlColumnDescriptor;

class AbstractAlterDdlCommand : public CodeElement {
public:
	explicit AbstractAlterDdlCommand(short kind);
	virtual ~AbstractAlterDdlCommand();

	virtual AbstractDdlLog* getCommandLog() = 0;

protected:
	DdlColumnDescriptor* copyColumnDescriptor(DdlColumnDescriptor* columnDescriptor) const;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_ */
