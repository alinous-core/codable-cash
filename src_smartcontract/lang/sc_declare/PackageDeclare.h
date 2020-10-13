/*
 * PackageDeclare.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_DECLARE_PACKAGEDECLARE_H_
#define SC_DECLARE_PACKAGEDECLARE_H_

#include "engine/sc/CodeElement.h"

namespace alinous {

class PackageNameDeclare;

class PackageDeclare : public CodeElement {
public:
	PackageDeclare();
	virtual ~PackageDeclare();

	void setName(PackageNameDeclare* name);
	const UnicodeString* getPackageName() noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	PackageNameDeclare* name;
};

} /* namespace alinous */

#endif /* SC_DECLARE_PACKAGEDECLARE_H_ */
