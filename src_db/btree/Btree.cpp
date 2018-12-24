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

#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "base_io/File.h"

namespace alinous {

Btree::Btree(File* folder, UnicodeString* name, DiskCacheManager* cacheManager) {
	this->folder = new File(*folder);
	this->name = new UnicodeString(name);
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
}

void Btree::create(BtreeConfig* config) {
	BtreeStorage newStore(this->folder, this->name);

	newStore.create(this->cacheManager, config);
}

void Btree::open(BtreeOpenConfig* config) {
	this->store = new BtreeStorage(this->folder, this->name);

	this->store->open(config->numDataBuffer, config->numNodeBuffer, this->cacheManager);

	BtreeHeaderBlock* header = this->store->loadHeader();
	StackRelease<BtreeHeaderBlock> __st_header(header);

	this->store->setRootFpos(header->getRootFpos());
	this->config = new BtreeConfig(header->getConfig());
}

void Btree::close() {
	this->store->close();
}

} /* namespace alinous */
