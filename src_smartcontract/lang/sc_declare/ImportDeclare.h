/*
 * ImportDeclare.h
 *
 *  Created on: 2019/06/17
 *      Author: iizuka
 */

#ifndef SC_DECLARE_IMPORTDECLARE_H_
#define SC_DECLARE_IMPORTDECLARE_H_

#include "engine/sc/CodeElement.h"

namespace alinous {

class UnicodeString;
class AnalyzeContext;

class ImportDeclare : public CodeElement {
public:
	ImportDeclare();
	virtual ~ImportDeclare();

	void appendStr(const char* cstr) noexcept;
	bool hasClassName(const UnicodeString* name) noexcept;
	UnicodeString* getPackageName() noexcept;

	void preAnalyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

private:
	UnicodeString* className;
	UnicodeString* namePart;
};

} /* namespace alinous */

#endif /* SC_DECLARE_IMPORTDECLARE_H_ */
