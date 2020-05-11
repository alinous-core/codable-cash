/*
 * SchemaBinary.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMABINARY_H_
#define SCHEMA_SCHEMABINARY_H_

#include "base/ArrayList.h"

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class SchemaBinary {
public:
	SchemaBinary();
	virtual ~SchemaBinary();

	void addSchemaName(const UnicodeString* name) noexcept;
private:
	ArrayList<UnicodeString> list;
};

} /* namespace codablecash */

#endif /* SCHEMA_SCHEMABINARY_H_ */
