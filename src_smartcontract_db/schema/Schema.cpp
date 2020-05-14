/*
 * Schema.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/Schema.h"
#include "schema/SchemaBinary.h"
#include "schema/ISchemaUptateListner.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "base_io/File.h"
#include "base_io/ByteBuffer.h"

#include "base_io_stream/FileOutputStream.h"
#include "base_io_stream/FileInputStream.h"


namespace codablecash {

const UnicodeString Schema::PUBLIC(L"public");
const UnicodeString Schema::SCHEMA_FILE(L"schema.bin");


Schema::Schema() {
	this->binary = nullptr;
	this->schemaBin = nullptr;
}

Schema::~Schema() {
	delete this->binary;
	delete this->schemaBin;
}

void Schema::addSchemaUpdateListner(ISchemaUptateListner* listner) noexcept {
	this->listners.addElement(listner);
}

void Schema::createSchema(const UnicodeString* name, File* baseDir) {
	SchemaBinary binary;

	binary.addSchemaName(&Schema::PUBLIC);
	File* scdir = baseDir->get(&Schema::PUBLIC); __STP(scdir);

	scdir->mkdirs();

	File* schemaBin = baseDir->get(&Schema::SCHEMA_FILE); __STP(schemaBin);

	FileOutputStream* outStream = new FileOutputStream(schemaBin); __STP(outStream);
	outStream->open(false);

	int size = binary.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	binary.toBinary(buff);

	const uint8_t* barray = buff->array();
	outStream->write((const char*)barray, size);
	outStream->flush();

	outStream->close();
}

void Schema::save() {
	FileOutputStream* outStream = new FileOutputStream(schemaBin); __STP(outStream);
	outStream->open(false);

	int size = this->binary->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	this->binary->toBinary(buff);

	const uint8_t* barray = buff->array();
	outStream->write((const char*)barray, size);
	outStream->flush();

	outStream->close();
}


void Schema::loadSchema(const File* baseDir) {
	this->schemaBin = baseDir->get(&Schema::SCHEMA_FILE);

	int size = schemaBin->length();
	char* b = new char[size]{};
	StackArrayRelease<char> br(b);

	FileInputStream* inStream = new FileInputStream(schemaBin); __STP(inStream);
	inStream->open();

	inStream->read(b, size);

	inStream->close();

	ByteBuffer* buff = ByteBuffer::wrapWithEndian((const uint8_t*)b, size, true); __STP(buff);

	this->binary = new SchemaBinary();
	this->binary->fromBinary(buff);

	fireSchemaLoaded();
}

uint64_t Schema::newTransactionId() {
	return this->binary->newTransactionId();
}

uint64_t Schema::newSchemaObjectId() noexcept {
	return this->binary->newSchemaObjectId();
}

void Schema::fireSchemaLoaded() noexcept {
	int maxLoop = this->listners.size();
	for(int i = 0; i != maxLoop; ++i){
		ISchemaUptateListner* l = this->listners.get(i);
		l->schemaLoaded(this);
	}
}

} /* namespace alinous */
