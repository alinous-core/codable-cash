/*
 * CdbBinaryObject.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef ENGINE_CDBBINARYOBJECT_H_
#define ENGINE_CDBBINARYOBJECT_H_

#include <cstdint>

namespace alinous {
class UnicodeString;
class ByteBuffer;
class TableIdentifier;
}
using namespace alinous;

namespace codablecash {

class CdbBinaryObject {
public:
	CdbBinaryObject();
	virtual ~CdbBinaryObject();

protected:
	int stringSize(UnicodeString* str) const noexcept;
	void putString(ByteBuffer* out, UnicodeString* str) const noexcept;
	UnicodeString* getString(ByteBuffer* in) const noexcept;

	void checkNotNull(CdbBinaryObject* object) const;
	void checkNotNull(UnicodeString* object) const;
	void checkNotNull(TableIdentifier* object) const;
};

} /* namespace codablecash */

#endif /* ENGINE_CDBBINARYOBJECT_H_ */
