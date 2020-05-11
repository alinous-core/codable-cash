/*
 * Schema.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/Schema.h"
#include "schema/SchemaBinary.h"

#include "base/UnicodeString.h"
#include "base_io/File.h"
#include "base/StackRelease.h"

namespace codablecash {

const UnicodeString Schema::PUBLIC(L"public");

Schema::Schema() {

}

Schema::~Schema() {
	// TODO Auto-generated destructor stub
}

void Schema::createSchema(const UnicodeString* name, File* baseDir) {
	SchemaBinary binary;

	binary.addSchemaName(&Schema::PUBLIC);
	File* scdir = baseDir->get(&Schema::PUBLIC); __STP(scdir);

	scdir->mkdirs();

}

} /* namespace alinous */
