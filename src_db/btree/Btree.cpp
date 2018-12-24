/*
 * Btree.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/Btree.h"
#include "btree/BtreeStorage.h"

#include "base/UnicodeString.h"
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
}

void Btree::close() {
	this->store->close();
}

} /* namespace alinous */
