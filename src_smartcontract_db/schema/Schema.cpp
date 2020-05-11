/*
 * Schema.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/Schema.h"
#include "schema/SchemaBinary.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "base_io/File.h"
#include "base_io/ByteBuffer.h"

#include "base_io_stream/FileOutputStream.h"

namespace codablecash {

const UnicodeString Schema::PUBLIC(L"public");
const UnicodeString Schema::SCHEMA_FILE(L"schema.bin");


Schema::Schema() {

}

Schema::~Schema() {
}

void Schema::createSchema(const UnicodeString* name, File* baseDir) {
	SchemaBinary binary;

	binary.addSchemaName(&Schema::PUBLIC);
	File* scdir = baseDir->get(&Schema::PUBLIC); __STP(scdir);

	scdir->mkdirs();

	File* schemaBin = scdir->get(&Schema::SCHEMA_FILE);

	FileOutputStream* outStream = new FileOutputStream(schemaBin);__STP(outStream);
	outStream->open(false);

	int size = binary.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	binary.toBinary(buff);

	const uint8_t* barray = buff->array();
	outStream->write((const char*)barray, size);
	outStream->flush();

	outStream->close();
}

} /* namespace alinous */
