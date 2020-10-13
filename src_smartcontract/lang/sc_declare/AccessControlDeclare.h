/*
 * AccessControlDeclare.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_ACCESSCONTROLDECLARE_H_
#define SC_DECLARE_ACCESSCONTROLDECLARE_H_

#include "engine/sc/CodeElement.h"

namespace alinous {

class AccessControlDeclare : public CodeElement {
public:
	static const constexpr char PUBLIC{1};
	static const constexpr char PROTECTED{2};
	static const constexpr char PRIVATE{3};

	AccessControlDeclare();
	virtual ~AccessControlDeclare();

	void setCtrl(char ctrl) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

private:
	char accessCtrl;
};

} /* namespace alinous */

#endif /* SC_DECLARE_ACCESSCONTROLDECLARE_H_ */
