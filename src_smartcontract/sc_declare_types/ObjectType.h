/*
 * ObjectType.h
 *
 *  Created on: 2019/06/09
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_OBJECTTYPE_H_
#define SC_DECLARE_TYPES_OBJECTTYPE_H_

#include "sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {
class PackageNameDeclare;
class UnicodeString;

class ObjectType : public AbstractPrimitiveType {
public:
	ObjectType();
	virtual ~ObjectType();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void setPackageName(PackageNameDeclare* packageName) noexcept;
	void setName(UnicodeString* className) noexcept;

private:
	PackageNameDeclare* packageName;
	UnicodeString* className;
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_OBJECTTYPE_H_ */
