/*
 * ShortType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_SHORTTYPE_H_
#define SC_DECLARE_TYPES_SHORTTYPE_H_

#include "lang/sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {

class ShortType : public AbstractPrimitiveType {
public:
	static const UnicodeString TYPE_NAME;

	ShortType();
	virtual ~ShortType();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual const UnicodeString* toString() noexcept;
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_SHORTTYPE_H_ */
