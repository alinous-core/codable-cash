/*
 * BoolType.h
 *
 *  Created on: 2019/06/11
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_BOOLTYPE_H_
#define SC_DECLARE_TYPES_BOOLTYPE_H_

#include "sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {

class BoolType : public AbstractPrimitiveType {
public:
	BoolType();
	virtual ~BoolType();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_BOOLTYPE_H_ */
