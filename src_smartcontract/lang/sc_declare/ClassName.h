/*
 * ClassName.h
 *
 *  Created on: 2019/06/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSNAME_H_
#define SC_DECLARE_CLASSNAME_H_

#include "engine/sc/CodeElement.h"

namespace alinous {

class UnicodeString;

class ClassName : public CodeElement {
public:
	ClassName();
	virtual ~ClassName();

	void addStr(const char* str) noexcept;
	void addStr(const UnicodeString* str) noexcept;
	const UnicodeString* getName() noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	UnicodeString* fqn;
};

} /* namespace alinous */

#endif /* SC_DECLARE_CLASSNAME_H_ */
