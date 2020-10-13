/*
 * VoidType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_VOIDTYPE_H_
#define SC_DECLARE_TYPES_VOIDTYPE_H_

#include "lang/sc_declare_types/AbstractType.h"

namespace alinous {

class VoidType : public AbstractType {
public:
	static const UnicodeString TYPE_NAME;

	VoidType();
	virtual ~VoidType();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual const UnicodeString* toString() noexcept;
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_VOIDTYPE_H_ */
