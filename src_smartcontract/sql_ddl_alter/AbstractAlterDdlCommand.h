/*
 * AbstractAlterDdlCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_
#define SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_

#include "sc/CodeElement.h"

namespace alinous {

class AbstractAlterDdlCommand : public CodeElement {
public:
	explicit AbstractAlterDdlCommand(short kind);
	virtual ~AbstractAlterDdlCommand();
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ABSTRACTALTERDDLCOMMAND_H_ */
