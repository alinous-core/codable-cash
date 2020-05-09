/*
 * DdlColumnDescriptor.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_DDLCOLUMNDESCRIPTOR_H_
#define SQL_DDL_DDLCOLUMNDESCRIPTOR_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {

class DdlColumnDescriptor : public AbstractSQLPart {
public:
	DdlColumnDescriptor();
	virtual ~DdlColumnDescriptor();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SQL_DDL_DDLCOLUMNDESCRIPTOR_H_ */
