/*
 * ObjectType.h
 *
 *  Created on: 2019/06/09
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_OBJECTTYPE_H_
#define SC_DECLARE_TYPES_OBJECTTYPE_H_

#include "lang/sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {
class PackageNameDeclare;
class UnicodeString;

class ObjectType : public AbstractType {
public:
	ObjectType();
	virtual ~ObjectType();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual const UnicodeString* toString() noexcept;

	void setPackageName(PackageNameDeclare* packageName) noexcept;
	void setName(UnicodeString* className) noexcept;

	PackageNameDeclare* getPackageName() const noexcept;
	const UnicodeString* getClassName() const noexcept;

private:
	PackageNameDeclare* packageName;
	UnicodeString* className;

	UnicodeString* str;
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_OBJECTTYPE_H_ */
