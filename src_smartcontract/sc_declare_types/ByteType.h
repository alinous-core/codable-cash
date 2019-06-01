/*
 * ByteType.h
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_BYTETYPE_H_
#define SC_DECLARE_TYPES_BYTETYPE_H_

#include "sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {

class ByteType : public AbstractPrimitiveType {
public:
	ByteType();
	virtual ~ByteType();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_BYTETYPE_H_ */
