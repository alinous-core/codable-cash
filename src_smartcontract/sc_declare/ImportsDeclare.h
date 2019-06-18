/*
 * ImportsDeclare.h
 *
 *  Created on: 2019/06/17
 *      Author: iizuka
 */

#ifndef SC_DECLARE_IMPORTSDECLARE_H_
#define SC_DECLARE_IMPORTSDECLARE_H_

#include "sc/CodeElement.h"
#include "base/ArrayList.h"

namespace alinous {
class ImportDeclare;

class ImportsDeclare : public CodeElement {
public:
	ImportsDeclare();
	virtual ~ImportsDeclare();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

private:
	ArrayList<ImportDeclare> list;
};

} /* namespace alinous */

#endif /* SC_DECLARE_IMPORTSDECLARE_H_ */
