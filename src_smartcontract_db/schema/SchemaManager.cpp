/*
 * Schema.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "schema/SchemaManager.h"
#include "schema/SchemaRoot.h"
#include "schema/ISchemaUptateListner.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "base_io/File.h"
#include "base_io/ByteBuffer.h"

#include "base_io_stream/FileOutputStream.h"
#include "base_io_stream/FileInputStream.h"


namespace codablecash {

const UnicodeString SchemaManager::PUBLIC(L"public");
const UnicodeString SchemaManager::SCHEMA_FILE(L"schema.bin");


SchemaManager::SchemaManager() {
	this->root = nullptr;
	this->schemaBin = nullptr;
	this->databaseBaseDir = nullptr;
}

SchemaManager::~SchemaManager() {
	delete this->root;
	delete this->schemaBin;
	delete this->databaseBaseDir;
}

void SchemaManager::addSchemaUpdateListner(ISchemaUptateListner* listner) noexcept {
	this->listners.addElement(listner);
}

void SchemaManager::createSchema(const UnicodeString* name, File* baseDir) {
	SchemaRoot root;

	root.addSchemaName(&SchemaManager::PUBLIC);
	File* scdir = baseDir->get(&SchemaManager::PUBLIC); __STP(scdir);

	scdir->mkdirs();

	File* schemaBin = baseDir->get(&SchemaManager::SCHEMA_FILE); __STP(schemaBin);

	FileOutputStream* outStream = new FileOutputStream(schemaBin); __STP(outStream);
	outStream->open(false);

	int size = root.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	root.toBinary(buff);

	const uint8_t* barray = buff->array();
	outStream->write((const char*)barray, size);
	outStream->flush();

	outStream->close();
}

void SchemaManager::save() {
	FileOutputStream* outStream = new FileOutputStream(schemaBin); __STP(outStream);
	outStream->open(false);

	int size = this->root->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	this->root->toBinary(buff);

	const uint8_t* barray = buff->array();
	outStream->write((const char*)barray, size);
	outStream->flush();

	outStream->close();
}


void SchemaManager::loadSchema(const File* baseDir) {
	this->databaseBaseDir = new File(*baseDir);
	this->schemaBin = baseDir->get(&SchemaManager::SCHEMA_FILE);

	int size = schemaBin->length();
	char* b = new char[size]{};
	StackArrayRelease<char> br(b);

	FileInputStream* inStream = new FileInputStream(schemaBin); __STP(inStream);
	inStream->open();

	inStream->read(b, size);

	inStream->close();

	ByteBuffer* buff = ByteBuffer::wrapWithEndian((const uint8_t*)b, size, true); __STP(buff);

	this->root = new SchemaRoot();
	this->root->fromBinary(buff);

	fireSchemaLoaded();
}

uint64_t SchemaManager::newTransactionId() {
	return this->root->newTransactionId();
}

uint64_t SchemaManager::newSchemaObjectId() noexcept {
	return this->root->newSchemaObjectId();
}

void SchemaManager::createTable(CdbTable* table) {
	const CdbTable* newTable = this->root->createTable(table);
	fireOnCreateTable(newTable);

	save();
}

void SchemaManager::fireSchemaLoaded() noexcept {
	int maxLoop = this->listners.size();
	for(int i = 0; i != maxLoop; ++i){
		ISchemaUptateListner* l = this->listners.get(i);
		l->schemaLoaded(this);
	}
}

void SchemaManager::fireOnCreateTable(const CdbTable* table) {
	int maxLoop = this->listners.size();
	for(int i = 0; i != maxLoop; ++i){
		ISchemaUptateListner* l = this->listners.get(i);
		l->onCreateTable(this, table);
	}

}

} /* namespace alinous */
