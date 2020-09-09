/*
 * AlterDropPrimaryKeyCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterDropPrimaryKeyCommand : public AbstractAlterDdlCommand {
public:
	AlterDropPrimaryKeyCommand();
	virtual ~AlterDropPrimaryKeyCommand();
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMAND_H_ */