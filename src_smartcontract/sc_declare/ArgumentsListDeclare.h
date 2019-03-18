/*
 * ArgumentsListDeclare.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_ARGUMENTSLISTDECLARE_H_
#define SC_DECLARE_ARGUMENTSLISTDECLARE_H_

#include "sc/CodeElement.h"
#include "base/ArrayList.h"

namespace alinous {

class ArgumentDeclare;

class ArgumentsListDeclare : public CodeElement {
public:
	ArgumentsListDeclare();
	virtual ~ArgumentsListDeclare();

	void addArgument(ArgumentDeclare* arg) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	ArrayList<ArgumentDeclare> list;
};

} /* namespace alinous */

#endif /* SC_DECLARE_ARGUMENTSLISTDECLARE_H_ */
