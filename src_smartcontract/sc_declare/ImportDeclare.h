/*
 * ImportDeclare.h
 *
 *  Created on: 2019/06/17
 *      Author: iizuka
 */

#ifndef SC_DECLARE_IMPORTDECLARE_H_
#define SC_DECLARE_IMPORTDECLARE_H_

#include "sc/CodeElement.h"

namespace alinous {

class ImportDeclare : public CodeElement {
public:
	ImportDeclare();
	virtual ~ImportDeclare();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SC_DECLARE_IMPORTDECLARE_H_ */
