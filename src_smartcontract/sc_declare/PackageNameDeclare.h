/*
 * PackageNameDeclare.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_PACKAGENAMEDECLARE_H_
#define SC_DECLARE_PACKAGENAMEDECLARE_H_

#include "sc/CodeElement.h"
#include "base/ArrayList.h"

namespace alinous {

class UnicodeString;

class PackageNameDeclare : public CodeElement {
public:
	PackageNameDeclare();
	virtual ~PackageNameDeclare();

	void addSegment(UnicodeString* seg);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	ArrayList<UnicodeString> list;
};

} /* namespace alinous */

#endif /* SC_DECLARE_PACKAGENAMEDECLARE_H_ */
