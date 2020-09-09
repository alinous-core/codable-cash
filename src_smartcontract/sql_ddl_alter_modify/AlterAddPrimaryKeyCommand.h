/*
 * AlterAddPrimaryKeyCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterAddPrimaryKeyCommand : public AbstractAlterDdlCommand {
public:
	AlterAddPrimaryKeyCommand();
	virtual ~AlterAddPrimaryKeyCommand();
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMAND_H_ */
