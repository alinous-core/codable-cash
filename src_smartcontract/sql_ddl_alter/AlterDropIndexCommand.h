/*
 * AlterDropIndexCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ALTERDROPINDEXCOMMAND_H_
#define SQL_DDL_ALTER_ALTERDROPINDEXCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterDropIndexCommand : public AbstractAlterDdlCommand {
public:
	explicit AlterDropIndexCommand(short kind);
	virtual ~AlterDropIndexCommand();
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ALTERDROPINDEXCOMMAND_H_ */
