/*
 * ClassExtends.h
 *
 *  Created on: 2019/06/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSEXTENDS_H_
#define SC_DECLARE_CLASSEXTENDS_H_

#include "sc/CodeElement.h"

namespace alinous {

class ClassName;

class ClassExtends : public CodeElement {
public:
	ClassExtends();
	virtual ~ClassExtends();

	void setClassName(ClassName* className) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	ClassName* className;
};

} /* namespace alinous */

#endif /* SC_DECLARE_CLASSEXTENDS_H_ */
