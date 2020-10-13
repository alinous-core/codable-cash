/*
 * AbstractType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_ABSTRACTTYPE_H_
#define SC_DECLARE_TYPES_ABSTRACTTYPE_H_

#include "engine/sc/CodeElement.h"
#include <cstdint>

namespace alinous {

class ByteBuffer;

class AbstractType : public CodeElement {
public:
	explicit AbstractType(short kind);
	virtual ~AbstractType();

	virtual const UnicodeString* toString() noexcept = 0;

	void addDimension() noexcept;
	int getDimension() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

private:
	uint8_t dimension;
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_ABSTRACTTYPE_H_ */
