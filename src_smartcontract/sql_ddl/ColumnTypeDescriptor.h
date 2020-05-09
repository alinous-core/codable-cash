/*
 * ColumnTypeDescriptor.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_COLUMNTYPEDESCRIPTOR_H_
#define SQL_DDL_COLUMNTYPEDESCRIPTOR_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {

class ColumnTypeDescriptor : public AbstractSQLPart {
public:
	ColumnTypeDescriptor();
	virtual ~ColumnTypeDescriptor();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SQL_DDL_COLUMNTYPEDESCRIPTOR_H_ */
