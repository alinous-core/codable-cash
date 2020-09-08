/*
 * AlterAddIndexCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ALTERADDINDEXCOMMAND_H_
#define SQL_DDL_ALTER_ALTERADDINDEXCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterAddIndexCommand : public AbstractAlterDdlCommand {
public:
	explicit AlterAddIndexCommand(short kind);
	virtual ~AlterAddIndexCommand();
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ALTERADDINDEXCOMMAND_H_ */
