/*
 * CharType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_CHARTYPE_H_
#define SC_DECLARE_TYPES_CHARTYPE_H_

#include "sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {

class CharType : public AbstractPrimitiveType {
public:
	static const UnicodeString TYPE_NAME;

	CharType();
	virtual ~CharType();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual const UnicodeString* toString() noexcept;
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_CHARTYPE_H_ */
