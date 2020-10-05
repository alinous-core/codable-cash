/*
 * Btree.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/Btree.h"
#include "btree/BtreeStorage.h"
#include "btree/BtreeHeaderBlock.h"
#include "btree/BtreeConfig.h"
#include "btree/NodeHandle.h"
#include "btree/NodeCursor.h"
#include "btree/BtreeScanner.h"

#include "btree/AbstractBtreeDataFactory.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "base_io/File.h"

#include "btreekey/BtreeKeyFactory.h"

namespace alinous {

Btree::Btree(const File* folder, const UnicodeString* name, DiskCacheManager* cacheManager, const BtreeKeyFactory* factory, const AbstractBtreeDataFactory* dfactory) {
	this->folder = new File(*folder);
	this->name = new UnicodeString(name);
	this->factory = factory->copy();
	this->dfactory = dfactory->copy();
	this->store = nullptr;
	this->cacheManager = cacheManager;

	this->config = nullptr;
}

Btree::~Btree() {
	if(this->store != nullptr){
		delete this->store, this->store = nullptr;
	}
	if(this->config != nullptr){
		delete this->config, this->config = nullptr;
	}
	delete this->name, this->name = nullptr;
	delete this->folder, this->folder = nullptr;
	delete this->factory;
	delete this->dfactory;
}

bool Btree::exists() const noexcept {
	BtreeStorage newStore(this->folder, this->name, this->factory, this->dfactory);
	return newStore.exists();
}

void Btree::create(const BtreeConfig* config) {
	BtreeStorage newStore(this->folder, this->name, this->factory, this->dfactory);

	newStore.create(this->cacheManager, config);
}

void Btree::clearFiles(const File* folder, const UnicodeString* name) {
	UnicodeString headerName(name);
	headerName.append(L"-header.bin");

	UnicodeString bodyName(name);
	bodyName.append(L".bin");

	File* headerFile = folder->get(&headerName); __STP(headerFile);
	File* bodyFile = folder->get(&bodyName); __STP(bodyFile);

	headerFile->deleteFile();
	bodyFile->deleteFile();
}


void Btree::renameFiles(const File* folder, const UnicodeString* lastName,	const UnicodeString* newName) {
	UnicodeString headerName(lastName);
	headerName.append(L"-header.bin");

	UnicodeString bodyName(lastName);
	bodyName.append(L".bin");

	File* headerFile = folder->get(&headerName); __STP(headerFile);
	File* bodyFile = folder->get(&bodyName); __STP(bodyFile);

	UnicodeString newHeaderName(newName);
	headerName.append(L"-header.bin");

	UnicodeString newBodyName(newName);
	bodyName.append(L".bin");

	File* newHeaderFile = folder->get(&headerName); __STP(newHeaderFile);
	File* newBodyFile = folder->get(&bodyName); __STP(newBodyFile);
	// TODO rename
}


void Btree::open(const BtreeOpenConfig* config) {
	this->store = new BtreeStorage(this->folder, this->name, this->factory, this->dfactory);

	this->store->open(config->numDataBuffer, config->numNodeBuffer, this->cacheManager);

	{
		BtreeHeaderBlock* header = this->store->loadHeader();
		StackRelease<BtreeHeaderBlock> __st_header(header);

		this->store->setRootFpos(header->getRootFpos());
		this->config = new BtreeConfig(header->getConfig());
	}
}

void Btree::close() noexcept {
	this->store->close();
}

void Btree::putData(const AbstractBtreeKey* key, const IBlockObject* data) {
	NodeHandle* rootNode = this->store->loadRoot();

	NodeCursor cursor(rootNode, this->store, this->config->nodeNumber);
	cursor.insert(key, data);
}



BtreeScanner* Btree::getScanner() {
	NodeHandle* rootNode = this->store->loadRoot();
	NodeCursor* cursor = new NodeCursor(rootNode, this->store, this->config->nodeNumber);

	return new BtreeScanner(cursor);
}

IBlockObject* Btree::findByKey(const AbstractBtreeKey* key) {
	NodeHandle* rootNode = this->store->loadRoot();
	NodeCursor* cursor = new NodeCursor(rootNode, this->store, this->config->nodeNumber);
	StackRelease<NodeCursor> __st_cursor(cursor);

	return cursor->find(key);
}

void Btree::remove(const AbstractBtreeKey* key) {
	NodeHandle* rootNode = this->store->loadRoot();
	NodeCursor* cursor = new NodeCursor(rootNode, this->store, this->config->nodeNumber);
	StackRelease<NodeCursor> __st_cursor(cursor);

	cursor->remove(key);
}

} /* namespace alinous */
